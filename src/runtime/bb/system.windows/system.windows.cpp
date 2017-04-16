
#include "../../stdutil/stdutil.h"
#include <bb/blitz/module.h>
#include <bb/runtime/runtime.h>
#include "system.windows.h"

#include <windows.h>
#include <map>
using namespace std;

typedef int (_stdcall *LibFunc)( const void *in,int in_sz,void *out,int out_sz );

struct gxDll{
	HINSTANCE hinst;
	map<string,LibFunc> funcs;
};

static map<string,gxDll*> libs;

WindowsSystemDriver::WindowsSystemDriver(){
	memset( &osinfo,0,sizeof(osinfo) );
	osinfo.dwOSVersionInfoSize=sizeof(osinfo);
	GetVersionEx( &osinfo );

	TIMECAPS tc;
	timeGetDevCaps( &tc,sizeof(tc) );
	timeBeginPeriod( tc.wPeriodMin );
}

WindowsSystemDriver::~WindowsSystemDriver(){
	TIMECAPS tc;
	timeGetDevCaps( &tc,sizeof(tc) );
	timeEndPeriod( tc.wPeriodMin );

	map<string,gxDll*>::const_iterator it;
	for( it=libs.begin();it!=libs.end();++it ){
		FreeLibrary( it->second->hinst );
	}
	libs.clear();
}

bool WindowsSystemDriver::isXPorLess(){
	return osinfo.dwMajorVersion<6;
}

static string toDir( string t ){
	if( t.size() && t[t.size()-1]!='\\' ) t+='\\';
	return t;
}

void WindowsSystemDriver::refreshSystemProperties(){
	char buff[MAX_PATH+1];

	bbSystemProperties["cpu"]="Intel";

	string os="Unknown";
	switch( osinfo.dwMajorVersion ){
	case 3:
		switch( osinfo.dwMinorVersion ){
		case 51:os="Windows NT 3.1";break;
		}
		break;
	case 4:
		switch( osinfo.dwMinorVersion ){
		case 0:os="Windows 95";break;
		case 10:os="Windows 98";break;
		case 90:os="Windows ME";break;
		}
		break;
	case 5:
		switch( osinfo.dwMinorVersion ){
		case 0:os="Windows 2000";break;
		case 1:os="Windows XP";break;
		case 2:os="Windows Server 2003";break;
		}
		break;
	case 6:
		switch( osinfo.dwMinorVersion ){
		case 0:os="Windows Vista";break;
		case 1:os="Windows 7";break;
		case 2:os="Windows 8";break;
		case 3:os="Windows 8.1";break;
		}
	case 10:
		switch( osinfo.dwMinorVersion ){
		case 0:os="Windows 10";break;
		}
		break;
	}

	bbSystemProperties["os"]=os;

	if( GetModuleFileName( 0,buff,MAX_PATH ) ){
		string t=buff;
		int n=t.find_last_of( '\\' );
		if( n!=string::npos ) t=t.substr( 0,n );
		bbSystemProperties["appdir"]=toDir( t );
	}

	if( GetWindowsDirectory( buff,MAX_PATH ) ) bbSystemProperties["windowsdir"]=toDir( buff );
	if( GetSystemDirectory( buff,MAX_PATH ) )  bbSystemProperties["systemdir"]=toDir( buff );
	if( GetTempPath( MAX_PATH,buff ) )         bbSystemProperties["tempdir"]=toDir( buff );
}

bool WindowsSystemDriver::delay( int ms ){
	int t=timeGetTime()+ms;
	for(;;){
		if( !bbRuntimeIdle() ) return false;
		int d=t-timeGetTime();	//how long left to wait
		if( d<=0 ) return true;
		if( d>100 ) d=100;
		Sleep( d );
	}
}

bool WindowsSystemDriver::execute( const string &cmd_line ){

	if( !cmd_line.size() ) return false;

	//convert cmd_line to cmd and params
	string cmd=cmd_line,params;
	while( cmd.size() && cmd[0]==' ' ) cmd=cmd.substr( 1 );
	if( cmd.find( '\"' )==0 ){
		int n=cmd.find( '\"',1 );
		if( n!=string::npos ){
			params=cmd.substr( n+1 );
			cmd=cmd.substr( 1,n-1 );
		}
	}else{
		int n=cmd.find( ' ' );
		if( n!=string::npos ){
			params=cmd.substr( n+1 );
			cmd=cmd.substr( 0,n );
		}
	}
	while( params.size() && params[0]==' ' ) params=params.substr( 1 );
	while( params.size() && params[params.size()-1]==' ' ) params=params.substr( 0,params.size()-1 );

	SetForegroundWindow( GetDesktopWindow() );

	return (int)ShellExecute( GetDesktopWindow(),0,cmd.c_str(),params.size() ? params.c_str() : 0,0,SW_SHOW )>32;
}

int WindowsSystemDriver::getMilliSecs(){
	return timeGetTime();
}

int WindowsSystemDriver::getScreenWidth( int i ){
  return GetSystemMetrics( SM_CXSCREEN );
}

int WindowsSystemDriver::getScreenHeight( int i ){
  return GetSystemMetrics( SM_CYSCREEN );
}

void WindowsSystemDriver::dpiInfo( float &scale_x,float &scale_y ){
	static bool calculated=false;
	static float _scale_x=1.0f,_scale_y=1.0f;

  if ( !calculated ){
		HDC hdc=GetDC( GetDesktopWindow() );
		_scale_x=GetDeviceCaps( hdc,LOGPIXELSX ) / 96.0f;
		_scale_y=GetDeviceCaps( hdc,LOGPIXELSY ) / 96.0f;
		ReleaseDC( GetDesktopWindow(),hdc );
		calculated=true;
	}

	scale_x=_scale_x;
	scale_y=_scale_y;
}

// TODO: figure out if this is broken on x64.
int WindowsSystemDriver::callDll( const std::string &dll,const std::string &func,const void *in,int in_sz,void *out,int out_sz ){

	map<string,gxDll*>::const_iterator lib_it=libs.find( dll );

	if( lib_it==libs.end() ){
		HINSTANCE h=LoadLibrary( dll.c_str() );
		if( !h ) return 0;
		gxDll *t=d_new gxDll;
		t->hinst=h;
		lib_it=libs.insert( make_pair( dll,t ) ).first;
	}

	gxDll *t=lib_it->second;
	map<string,LibFunc>::const_iterator fun_it=t->funcs.find( func );

	if( fun_it==t->funcs.end() ){
		LibFunc f=(LibFunc)GetProcAddress( t->hinst,func.c_str() );
		if( !f ) return 0;
		fun_it=t->funcs.insert( make_pair( func,f ) ).first;
	}

#if defined(_MSC_VER) && !defined(WIN64)
	static void *save_esp;

	_asm{
		mov	[save_esp],esp
	};
#endif

	int n=fun_it->second( in,in_sz,out,out_sz );

#if defined(_MSC_VER) && !defined(WIN64)
	_asm{
		mov esp,[save_esp]
	};
#endif

	return n;
}

extern inline void debugBank( bbBank *b );
extern inline void debugBank( bbBank *b,int offset );

int BBCALL bbCallDLL( BBStr *dll,BBStr *fun,bbBank *in,bbBank *out ){
	if( bb_env.debug ){
		if( in ) debugBank( in );
		if( out ) debugBank( out );
	}
	int t=((WindowsSystemDriver*)bbSystemDriver)->callDll( *dll,*fun,
		in ? in->data : 0,in ? in->size : 0,
		out ? out->data : 0,out ? out->size : 0 );
	delete dll;delete fun;
	return t;
}

BBMODULE_CREATE( system_windows ){
	if( !bbSystemDriver ){
		bbSystemDriver=d_new WindowsSystemDriver();
	}
	return true;
}

BBMODULE_DESTROY( system_windows ){
	return true;
}

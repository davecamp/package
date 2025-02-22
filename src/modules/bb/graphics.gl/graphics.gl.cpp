#include "../stdutil/stdutil.h"
#include "graphics.gl.h"

#include <vector>

GLuint _bbGLCompileShader( GLenum type,const std::string &name,const std::string &source ){
#ifdef BB_DESKTOP
	static char version[]         = "#version 330    \n";
#else
	static char version[]         = "#version 300 es \n";
#endif
	static char define_vertex[]   = "#define VERTEX  \n";
	static char define_fragment[] = "#define FRAGMENT\n";

	const char *sources[] = {
		version,
		type==GL_VERTEX_SHADER?define_vertex:define_fragment,
		source.c_str()
	};
	int source_lens[] = { 17,17,(int)source.size() };

	GLuint shader=GL( glCreateShader( type ) );
	GL( glShaderSource( shader,3,sources,source_lens ) );
	GL( glCompileShader( shader ) );

	GLint status;
	GL( glGetShaderiv(shader, GL_COMPILE_STATUS, &status) );
	if( status==0 ){
		LOGD( "Couldn't compile shader: %s\n",name.c_str() );
		GLint logLength;
		GL( glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength) );
		if( logLength>0 ){
			GLchar *log = (GLchar*)malloc(logLength);
			GL( glGetShaderInfoLog(shader, logLength, &logLength, log) );
			if( log[0]!=0 ){
				LOGD( "Shader log: %s\n",log );
			}
			free( log );
		}
		GL( glDeleteShader(shader) );

		shader=0;
	}
	return shader;
}

GLuint _bbGLCompileProgram( const std::string &name,const std::string &src ){
	GLuint vert=_bbGLCompileShader( GL_VERTEX_SHADER,name,src );
	GLuint frag=_bbGLCompileShader( GL_FRAGMENT_SHADER,name,src );

	if( vert==0||frag==0 ){
		LOGD( "%s","Failed to compile shader" );
		exit(1);
	}
	GLuint program=GL( glCreateProgram() );

	GL( glAttachShader( program,vert ) );
	GL( glAttachShader( program,frag ) );

	int link_status=0;
	GL( glLinkProgram( program ) );
	GL( glGetProgramiv( program,GL_LINK_STATUS,&link_status ) );
	if( !link_status ){
		LOGD( "%s","Failed to link linker" );

		GLint maxLength = 0;
		GL( glGetProgramiv( program,GL_INFO_LOG_LENGTH,&maxLength ) );

		GLchar *log=(GLchar*)malloc( maxLength );
		GL( glGetProgramInfoLog( program,maxLength,&maxLength,&log[0] ) );
		if( log[0]!=0 ){
			LOGD( "%s",log );
		}
		free( log );

		exit(1);
	}

	GL( glDeleteShader( vert ) );
	GL( glDeleteShader( frag ) );

	return program;
}

static
const char * GlErrorString( GLenum error ) {
	switch ( error ) {
  case GL_NO_ERROR:                      return "GL_NO_ERROR";
  case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
  case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
  case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
  case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
  default: return "unknown";
	}
}

const char * bbGLFramebufferStatusString( GLenum status ) {
	switch ( status ) {
	case GL_FRAMEBUFFER_COMPLETE:                      return "GL_FRAMEBUFFER_COMPLETE";
	case GL_FRAMEBUFFER_UNDEFINED:                     return "GL_FRAMEBUFFER_UNDEFINED";
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
	case GL_FRAMEBUFFER_UNSUPPORTED:                   return "GL_FRAMEBUFFER_UNSUPPORTED";
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
#ifdef GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
#endif
	default:                                           return "unknown";
	}
}

void bbGLGraphicsCheckErrors( const char *file, int line ){
	for( int i=0;i<10;i++ ){
		const GLenum error=glGetError();
		if( error==GL_NO_ERROR ){
			break;
		}
		LOGD( "GL error on %s:%d: %s", file, line, GlErrorString( error ) );
	}
}

GLGraphics::GLGraphics(){
}

bool GLGraphics::init(){
	def_font=(BBImageFont*)loadFont( "courier",12,0 );
	if( def_font==0 ){
		def_font=(BBImageFont*)loadFont( "courier new",12,0 );
	}

	return def_font!=0;
}

BBFont *GLGraphics::getDefaultFont()const{
	return def_font;
}

//OBJECTS
BBCanvas *GLGraphics::createCanvas( int width,int height,int flags ){
	BBCanvas *canvas=d_new GLTextureCanvas( &res,width,height,flags );
	canvas_set.insert( canvas );
	return canvas;
}

BBCanvas *GLGraphics::loadCanvas( const std::string &file,int flags ){
	BBPixmap *pixmap=bbLoadPixmap( file );
	if( !pixmap ) return 0;

	pixmap->flipVertically();

	BBCanvas *canvas=d_new GLTextureCanvas( &res,pixmap,flags );
	canvas_set.insert( canvas );
	delete pixmap;
	return canvas;
}

BBMovie *GLGraphics::openMovie( const std::string &file,int flags ){
	return 0;
}


BBMODULE_CREATE( graphics_gl ){
	return true;
}

BBMODULE_DESTROY( graphics_gl ){
	return true;
}

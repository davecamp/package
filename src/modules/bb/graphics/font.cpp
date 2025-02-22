
#include "../stdutil/stdutil.h"
#include <bb/system/system.h>
#include "font.h"

#undef max

FT_Library ft;
std::map<std::string,BBFontData> bbFontCache;

BBFont::~BBFont(){
}

BBImageFont::BBImageFont( FT_Face f,int height,float d ):face(f),atlas(0){
	// TODO: this isn't quite right...
	FT_Set_Char_Size( face,0,(height-3)*64*d,0,0 );
	baseline=height;
	density=1.0/d;
}

BBImageFont *BBImageFont::load( const std::string &name,int height,float density,int flags ){
	BBFontData font;

	if( bbFontCache.count( name )==0 ){
		if( bbSystemDriver->lookupFontData( name,font ) ){
			bbFontCache.insert( make_pair( name,font ) );
		}else{
			return 0;
		}
	}else{
		font=bbFontCache[name];
	}

	FT_Face face;
	if( FT_New_Memory_Face( ft,font.data,font.size,0,&face ) ){
		return 0;
	}
	return d_new BBImageFont( face,height,density );
}

bool BBImageFont::loadChars( const std::string &t )const{
	for( int i=0;i<t.length();i++ ){
		if( !characters.count(t[i]) ){
			Char chr;
			chr.index=FT_Get_Char_Index( face,t[i] );
			FT_Load_Glyph( face,chr.index,FT_LOAD_RENDER );

			chr.width=face->glyph->bitmap.width;
			chr.height=face->glyph->bitmap.rows;
			chr.bearing_x=face->glyph->bitmap_left;
			chr.bearing_y=face->glyph->bitmap_top;
			chr.advance=face->glyph->advance.x>>6;

			characters.insert( std::make_pair( t[i],chr ) );

			dirty=true;
		}
	}

	return dirty;
}

void BBImageFont::rebuildAtlas(){
	if( !dirty ) return;

	delete atlas;
	atlas=d_new BBPixmap;
	atlas->width=atlas->height=256;
	atlas->bits=new unsigned char[atlas->width*atlas->height];
	memset( atlas->bits,0,atlas->width*atlas->height );

	int ox=0,oy=0,my=0;
	for( std::map<char,Char>::iterator it=characters.begin();it!=characters.end();++it ){
		Char &c=it->second;

		FT_Load_Glyph( face,c.index,FT_LOAD_RENDER );

		if( ox+c.width>=atlas->width ){
			oy+=my;
			ox=my=0;
		}

		c.x=ox;c.y=oy;

		int width=face->glyph->bitmap.width;

		my=std::max( c.height,my );

		for( int y=0;y<face->glyph->bitmap.rows;y++ ){
			memcpy( atlas->bits+(atlas->width*(oy+y))+ox,face->glyph->bitmap.buffer+y*width,width );
		}

		ox+=c.width;
	}

	dirty=false;
}

BBImageFont::Char &BBImageFont::getChar( char c ){
	loadChars( std::string( 1,c ) );
	return characters[c];
}

float BBImageFont::getKerning( char l,char r ){
	if( !FT_HAS_KERNING(face) ) return 0;
	Char lc=getChar( l ),rc=getChar( r );

	FT_Vector delta;
	FT_Get_Kerning( face,lc.index,rc.index,FT_KERNING_DEFAULT,&delta );
	return (delta.x>>6)*density;
}

int BBImageFont::getWidth()const{
	return 0;
}

int BBImageFont::getHeight()const{
	return baseline;
}

int BBImageFont::getWidth( const std::string &text )const{
	loadChars( text );

	int width=0;
	for( int i=0;i<text.length();i++ ){
		width+=characters[text[i]].advance*density;
	}
	return width;
}

bool BBImageFont::isPrintable( int chr )const{
	return true;
}

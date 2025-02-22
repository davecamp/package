#ifndef BB_STRING_COMMANDS_H
#define BB_STRING_COMMANDS_H

#include <bb/blitz/module.h>
#include <bb/string/string.h>

#ifdef __cplusplus
extern "C" {
#endif

// AUTOGENERATED. DO NOT EDIT.
// RUN `make` TO UPDATE.
BBStr * BBCALL bbString( BBStr *string,bb_int_t repeat );
BBStr * BBCALL bbLeft( BBStr *string,bb_int_t count );
BBStr * BBCALL bbRight( BBStr *string,bb_int_t count );
BBStr * BBCALL bbReplace( BBStr *string,BBStr *from,BBStr *to );
bb_int_t BBCALL bbInstr( BBStr *string,BBStr *find,bb_int_t from );
BBStr * BBCALL bbMid( BBStr *string,bb_int_t start,bb_int_t count );
BBStr * BBCALL bbUpper( BBStr *string );
BBStr * BBCALL bbLower( BBStr *string );
BBStr * BBCALL bbTrim( BBStr *string );
BBStr * BBCALL bbLSet( BBStr *string,bb_int_t size );
BBStr * BBCALL bbRSet( BBStr *string,bb_int_t size );
BBStr * BBCALL bbChr( bb_int_t ascii );
bb_int_t BBCALL bbAsc( BBStr *string );
bb_int_t BBCALL bbLen( BBStr *string );
BBStr * BBCALL bbHex( bb_int_t value );
BBStr * BBCALL bbBin( bb_int_t value );
BBStr * BBCALL bbCurrentDate(  );
BBStr * BBCALL bbCurrentTime(  );

#ifdef __cplusplus
}
#endif


#endif

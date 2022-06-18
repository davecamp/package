#ifndef BB_SYSTEM_COMMANDS_H
#define BB_SYSTEM_COMMANDS_H

#include <bb/blitz/module.h>
#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif

// AUTOGENERATED. DO NOT EDIT.
// RUN `make` TO UPDATE.
bb_int_t BBCALL bbExecFile( BBStr *file );
void BBCALL bbDelay( bb_int_t millisecs );
bb_int_t BBCALL bbMilliSecs(  );
BBStr * BBCALL bbSystemProperty( BBStr *property );
BBStr * BBCALL bbGetEnv( BBStr *env_var );
void BBCALL bbSetEnv( BBStr *env_var,BBStr *value );
bb_int_t BBCALL bbScreenWidth( bb_int_t i );
bb_int_t BBCALL bbScreenHeight( bb_int_t i );
bb_float_t BBCALL bbDPIScaleX(  );
bb_float_t BBCALL bbDPIScaleY(  );

#ifdef __cplusplus
}
#endif


#endif

// AUTOGENERATED. DO NOT EDIT.
// RUN `make` TO UPDATE.

#include <bb/blitz/module.h>
#include <bb/stdio/stdio.h>

#ifdef WIN32
BBMODULE_LINK( stdio ){
	rtSym( "WriteStdout$str",bbWriteStdout );
	rtSym( "WriteStderr$str",bbWriteStderr );
}
#endif

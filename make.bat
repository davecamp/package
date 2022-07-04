REM @echo off

set ENV=%1
set PLATFORM=%2

IF NOT "%ENV%" == "debug" (
  IF NOT "%ENV%" == "release" (
    SET ENV=debug
  )
)

IF "%ENV%" == "debug" (
  SET CONFIG=Debug
)
IF "%ENV%" == "release" (
  SET CONFIG=Release
)

IF "%VisualStudioVersion%" == "16.0" (
  SET GENERATOR=Visual Studio 16 2019
)

IF "%VisualStudioVersion%" == "17.0" (
  SET GENERATOR=Visual Studio 17 2022
)

IF NOT "%PLATFORM%" == "win32" (
  IF NOT "%PLATFORM%" == "win64" (
    IF NOT "%PLATFORM%" == "woa64" (
      SET PLATFORM=win32
    )
  )
)

IF "%PLATFORM%" == "win32" (
  SET ARCH=Win32
)

IF "%PLATFORM%" == "win64" (
  SET ARCH=x64
)

IF "%PLATFORM%" == "woa64" (
  SET ARCH=ARM64
)

ECHO Building %PLATFORM% in %ENV% mode using VS %VisualStudioVersion%.

set OUTPUT=_release\toolchains\%PLATFORM%
set RELEASE=_release

cmake -G "%GENERATOR%" -H. -B"%cd%\build\%PLATFORM%\%ENV%" -A%ARCH% -DBB_PLATFORM=%PLATFORM% -DBB_ENV=%ENV% || exit /b 1
msbuild /nologo /verbosity:normal /m build\%PLATFORM%\%ENV%\Blitz3D.sln /property:Configuration=%CONFIG% /property:Platform=%ARCH% || exit /b 1

COPY /Y deps\fmod\bin\fmod*.dll %RELEASE%\bin
COPY /Y %OUTPUT%\bin\unit_test.dll %RELEASE%\userlibs
COPY /Y src\modules\bb\unit-test\unit_test.decls %RELEASE%\userlibs

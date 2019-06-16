@echo off & setlocal enabledelayedexpansion

call :crt_manifest_dependency
echo CRT_MANIFEST_DP: [%CRT_MANIFEST_DP%]

ml /nologo /c /coff /Zi /Fl HelloAsm.asm
link /NOLOGO /SUBSYSTEM:CONSOLE /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF "%CRT_MANIFEST_DP%" HelloAsm.obj
mt -nologo -manifest HelloAsm.exe.manifest -outputresource:HelloAsm.exe

goto :EOF

rem --------------------------------------------------------------------------------------------------------------------
rem Subroutines
rem --------------------------------------------------------------------------------------------------------------------

:crt_manifest_dependency
setlocal
set CLPATH=
set REDISTDIR=
set CRTNAME=
set ASMID=

for /f "usebackq tokens=*" %%I in (`where cl`) do set CLPATH=%%I
set REDISTDIR=%CLPATH:bin\cl.exe=redist\x86\%
for /f "usebackq tokens=*" %%I in (`dir /b "%REDISTDIR%" ^| findstr /c:CRT`) do set CRTNAME=%%I
set CRTMF=%REDISTDIR%%CRTNAME%\%CRTNAME%.manifest

for /f "usebackq tokens=*" %%I in (`findstr /c:assemblyIdentity "%CRTMF%"`) do set ASMID=%%I
set ASMID=%ASMID:~18,-20%
set ASMID=%ASMID:"='%
set MFDP=/manifestdependency:%ASMID% language='*'

rem echo CLPATH: [%CLPATH%]
rem echo REDISTDIR: [%REDISTDIR%]
rem echo CRTNAME: [%CRTNAME%]
rem echo CRTMF: [%CRTMF%]
rem echo ASMID: [%ASMID%]
rem echo MFDP: [%MFDP%]
endlocal & set CRT_MANIFEST_DP=%MFDP%
exit /b

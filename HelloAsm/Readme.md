# HelloAsm

This is a hello-world console example of MASM program, which is dynamically linked against MSVCRT DLL of specific-version MSVC (msvcr[ver].dll).

This simplest program may be used as the start code for making quick and dirty MASM test.

The build batch file "makeit.bat", infers the side-by-side (SxS) manifest dependency of msvcr[ver].dll from current building environment (VS Command Prompt), used as link option.

; Common.inc
;

.nolist

; ----------------------------------------------------------------------------------------------------------------------
; Windows API Declarations
; ----------------------------------------------------------------------------------------------------------------------

includelib kernel32.lib

ExitProcess proto stdcall :dword
exit macro exitCode
    invoke ExitProcess, exitCode
endm

; ----------------------------------------------------------------------------------------------------------------------
; CRT Routines Declarations
; ----------------------------------------------------------------------------------------------------------------------

includelib msvcrt.lib

; int puts(const char* str)
puts proto c :dword
; int fputs(const char* str, FILE* stream)
fputs proto c :dword, :dword
; int _getch()
_getch proto c
; int printf(const char* fmt, ...)
printf proto c :dword, :vararg
; int fprintf(FILE* stream, const char* fmt, ...)
fprintf proto c :dword, :dword, :vararg
; char* fgets(char* str, int n, FILE* stream)
fgets proto c :dword, :dword, :dword
; int puts(const char* str)
puts proto c :dword
; int fputc(int c, FILE* stream)
fputc proto c :dword, :dword
; int sscanf(const char* buf, const char* fmt, ...)
sscanf proto c :dword, :dword, :vararg

; Implemented in StdStream.cpp
; FILE* get_stdin()
get_stdin proto c
; FILE* get_stdout()
get_stdout proto c
; FILE* get_stderr()
get_stderr proto c

; ----------------------------------------------------------------------------------------------------------------------
; String Helper in StrHelper.cpp
; ----------------------------------------------------------------------------------------------------------------------

; char* rtrim(_Inout_ char* str)
rtrim proto c :dword
; char* ltrim(_Inout_ char* str)
ltrim proto c :dword
; char* trim(_Inout_ char* str)
trim proto c :dword

; ----------------------------------------------------------------------------------------------------------------------
; Euclid in Euclid.asm
; ----------------------------------------------------------------------------------------------------------------------

Euclid proto c :sdword, :sdword

; ----------------------------------------------------------------------------------------------------------------------
; Globals
; ----------------------------------------------------------------------------------------------------------------------

LF = 0Ah
CR = 0Dh

INT_MAX = 7fffffffh

.const
    PMT_EXIT    byte 'Press any key to Exit...', 0
    BNR_TEST    byte '----- Test TestModule -----', 0
    FMT_VA      byte '0x%p', 0
    PFX_ESP     byte 'ESP: ', 0

.data
    stdin   dword ?
    stdout  dword ?
    stderr  dword ?

; ----------------------------------------------------------------------------------------------------------------------
; Diagnostics Helpers
; ----------------------------------------------------------------------------------------------------------------------

printlf macro stream
    invoke fputc, LF, stream
endm

printesp macro stream
    push eax
    push ecx
    push edx
    invoke fputs, offset PFX_ESP, stream
    invoke fprintf, stream, offset FMT_VA, esp
    printlf stream
    pop edx
    pop ecx
    pop eax
endm

; ----------------------------------------------------------------------------------------------------------------------
; Setup
; ----------------------------------------------------------------------------------------------------------------------

.code
setup proc
    ; Initialize globals of stdin, stdout, stderr
    invoke get_stdin
    mov stdin, eax
    invoke get_stdout
    mov stdout, eax
    invoke get_stderr
    mov stderr, eax
    ret
setup endp

.list

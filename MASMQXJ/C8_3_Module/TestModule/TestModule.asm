; TestModule.asm
;

.686
.model flat, c
option casemap:none

include Common.inc

; ----------------------------------------------------------------------------------------------------------------------
; Globals
; ----------------------------------------------------------------------------------------------------------------------

__EXIT_PROMPT__ = 1
DEF_BUF_SIZE    = 512

.const
    FMT_PROMPT  byte "Find the greatest common divisor (GCD) of two numbers by Euclid's algorithm.", LF
                byte "Enter two positive integers, that is in range (0, %d], separated by whitespace.", LF, 0
    PMT_IN      byte '> ', 0

    FMT_SCAN    byte '%d%d', 0
    FMT_OUTSTR  byte 'In: [%s]', LF, 0
    FMT_OUTGCD  byte 'GCD(%d, %d): %d', LF, 0

    ERR_INVALID byte 'Invalid input. Require two positive integers.', LF, 0

.data
    g_Err       dword 0
    g_Buf       byte DEF_BUF_SIZE dup(?)
    g_Num       sdword ?, ?

; ----------------------------------------------------------------------------------------------------------------------
; Program Entry
; ----------------------------------------------------------------------------------------------------------------------

.code
start:
    invoke setup
    invoke puts, offset BNR_TEST

ifdef __DEBUG__
    printesp stderr
endif
    invoke printf, offset FMT_PROMPT, INT_MAX
    invoke fputs, offset PMT_IN, stdout

    invoke fgets, offset g_Buf, lengthof g_Buf, stdin
    test eax, eax   ; fgets returns NULL, that means getting stream error or EOF.
    jz EXIT

    invoke trim, offset g_Buf
    invoke printf, offset FMT_OUTSTR, offset g_Buf

    ; if (sscanf(g_Buf, "%d%d", &g_Num[0], &g_Num[1]) != 2 || g_Num[0] <= 0 || g_Num[1] <= 0)
    ;     invalid_input();
    invoke sscanf, offset g_Buf, offset FMT_SCAN, offset g_Num, offset g_Num[type g_Num]
    cmp eax, 2
    jne INVALID_INPUT
    cmp g_Num, 0
    jle INVALID_INPUT
    cmp g_Num[type g_Num], 0
    jg CONT
INVALID_INPUT:
    invoke fputs, offset ERR_INVALID, stderr
    mov g_Err, 1
    jmp EXIT
CONT:

    invoke Euclid, g_Num, g_Num[type g_Num]
    invoke printf, offset FMT_OUTGCD, g_Num, g_Num[type g_Num], eax
ifdef __DEBUG__
    printesp stderr
endif

EXIT:
if __EXIT_PROMPT__
    invoke puts, offset PMT_EXIT
    invoke _getch
endif

    exit g_Err
end start

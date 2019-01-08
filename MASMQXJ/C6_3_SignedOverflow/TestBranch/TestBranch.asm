; TestBranch.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_OF     byte '----- test singed overflow -----', 0Dh, 0Ah, 0
    MSG_RES byte 'Res: ', 0
    MSG_OF  byte 'Error: Overflow', 0

    ; 32bit 有符号整数取值范围 [–2147483648, 2147483647]
    dvar1 dword 2147483600
    dvar2 dword -48

.code
start:
    mov eax, offset MSG_TEST_OF
    call dispmsg

    ; 使用双分支结构,  判断有符号数运算是否溢出
    mov eax, dvar1
    sub eax, dvar2
    jo ERR_OF

    ; 无溢出时
    mov ebx, eax
    mov eax, offset MSG_RES
    call dispmsg
    mov eax, ebx
    call dispsid
    jmp CALC_END
ERR_OF:
    ; 溢出时
    mov eax, offset MSG_OF
    call dispmsg
CALC_END:
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

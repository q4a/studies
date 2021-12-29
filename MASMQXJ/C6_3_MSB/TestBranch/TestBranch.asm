; TestBranch.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_MSB        byte '----- test MSB -----', 0Dh, 0Ah, 0

    dvar dword 80000000h

.code
start:
    mov eax, offset MSG_TEST_MSB
    call dispmsg

    ; 使用双分支结构, 显示数据的最高位 MSB (Most Significant Bit)
    mov ebx, dvar
    shl ebx, 1      ; MSB 移入 CF
    jc MSB_1        ; CF = 1 跳转
    mov al, '0'     ; CF = 0 时, 顺序执行到这里
    jmp SHOW
MSB_1:
    mov al, '1'
SHOW:
    call dispc
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

; TestJmp.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    nvar dword ?

.code
start:
    jmp LABEL_1
    nop

LABEL_1:
    jmp near ptr LABEL_2
    nop

LABEL_2:
    mov eax, offset LABEL_3
    jmp eax
    nop

LABEL_3:
    mov eax, offset LABEL_4
    mov nvar, eax
    mov ebx, offset nvar
    jmp near ptr [ebx]
    nop

LABEL_4:
    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

; TestPush.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    TEN = 10
    dvar dword 67762000h, 12345678h

.code
start:
    mov eax, dvar + 4
    push eax
    push dword ptr TEN
    push dvar
    pop eax
    pop dvar + 4
    mov ebx, dvar + 4
    pop ecx

    call disprd

    exit 0
end start

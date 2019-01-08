; TestAddr.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    msg     byte '12345678', 0Dh, 0Ah, 0
    org     10h
    bvar1   byte 0EFh
    align   2
    wvar2   word 0CDEFh
    align   4
    dvar3   dword 89ABCDEFh
    align   4
    dvar4   dword 12345678h

.code
start:
    mov eax, offset msg
    call dispmsg

    exit 0
end start

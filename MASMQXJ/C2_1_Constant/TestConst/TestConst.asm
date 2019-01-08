; TestConst.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    ; 字符串常量里用 !!!! 表示一个 !
    MSG_HELLO equ <'Hello World!!!!'>
    CR = 0Dh
    LF = 0Ah

    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    bvar    byte 100, 64h, 01100100b, 'd', 'a'
    msg     byte MSG_HELLO, '0123456789'
    CRLF    byte CR, LF, 0

.code
start:
    mov al, bvar[4]
    call dispc
    call dispcrlf

    mov eax, offset msg
    call dispmsg

    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

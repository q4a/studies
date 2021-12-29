; TestVar.asm
;

; IO ×Ó³ÌÐòÉùÃ÷
; .686, .model flat, stdcall
include io32.inc

.data
    msg     byte 'Hello', 0Dh, 0Ah, 0
    bvar1   byte 0, 255, -1, 128, -128, +127
    bvar2   byte ?
    bvar3   byte 5 dup('$')
    MININT  = 10
    bvar4   byte MININT dup(0), MININT dup(MININT, ?)
            byte 2 dup(2, 3, 2 dup(4))

.code
start:
    mov eax, offset msg
    call dispmsg

    exit 0
end start

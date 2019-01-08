; TestLea.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    bvar    byte    '1234567', 0, 'abcdefg', 0, 'higklmn', 0

.code
start:
    mov ebx, 1  ; row
    mov edi, 2  ; col
    lea eax, [bvar + ebx * 8 + edi]

    call dispmsg

    exit 0
end start

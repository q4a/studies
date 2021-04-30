; TestALU.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_ADD byte '----- test add -----', 0Dh, 0Ah, 0
    MSG_TEST_SUB byte '----- test sub -----', 0Dh, 0Ah, 0
    MSG_TEST_CASECONVERT byte '----- test char case convert -----', 0Dh, 0Ah, 0
    MSG_I_UPPER byte 'Enter an uppercase char: ', 0
    MSG_O_LOWER byte 'Lowercase char: ', 0
    MSG_I_LOWER byte 'Enter an lowercase char: ', 0
    MSG_O_UPPER byte 'Uppercase char: ', 0

.code
start:
    ; 测试 add 指令
    mov eax, offset MSG_TEST_ADD
    call dispmsg
    mov eax, 0AAFF7348H
    add al, 27H         ; 8bit 加法
    call disprf
    call disphb
    call dispcrlf

    add ax, 3FFFH       ; 16bit 加法
    call disprf
    call disphw
    call dispcrlf

    add eax, 88000000H   ; 32bit 加法
    call disprf
    call disphd
    call dispcrlf

    ; 测试 sub 指令
    mov eax, offset MSG_TEST_SUB
    call dispmsg
    mov eax, 0AAFF7348H
    sub al, 27H         ; 8bit 减法
    call disprf
    call disphb
    call dispcrlf

    sub ax, 3FFFH       ; 16bit 减法
    call disprf
    call disphw
    call dispcrlf

    sub eax, 0BB000000H ; 32bit 减法
    call disprf
    call disphd
    call dispcrlf

    ; 测试大小写字母转换
    mov eax, offset MSG_TEST_CASECONVERT
    call dispmsg

    ; 大写字母转换为小写, 使用 add
    mov eax, offset MSG_I_UPPER
    call dispmsg
    call readc
    mov bl, al
    call dispcrlf
    mov eax, offset MSG_O_LOWER
    call dispmsg
    mov al, bl
    add al, 20h
    call dispc
    call dispcrlf

    ; 小写字母转换为大写, 使用 sub
    mov eax, offset MSG_I_LOWER
    call dispmsg
    call readc
    mov bl, al
    call dispcrlf
    mov eax, offset MSG_O_UPPER
    call dispmsg
    mov al, bl
    sub al, 20h
    call dispc

    ; 程序结束提示
    call dispcrlf
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

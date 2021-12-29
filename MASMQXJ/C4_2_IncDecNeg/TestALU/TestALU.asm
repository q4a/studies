; TestALU.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    BUF_SIZE = 256

    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_INC    byte '----- test inc -----', 0Dh, 0Ah, 0
    MSG_TEST_DEC    byte '----- test dec -----', 0Dh, 0Ah, 0
    MSG_TEST_NEG    byte '----- test neg -----', 0Dh, 0Ah, 0

    MSG_I_STR       byte 'Enter a string: ', 0
    MSG_O_STR       byte 'String: ', 0
    MSG_LEN         byte 'Len: ', 0

    MSG_I_HEX       byte 'Enter a hex-byte (00~ff): ', 0
    MSG_O_NEGBIN    byte 'Neg '
    MSG_O_BIN       byte 'Bin: ', 0
    MSG_SIGNED_DEC  byte ' Signed Dec: ', 0

    strbuf          byte BUF_SIZE dup(?)

.code
start:
    ; 测试 inc 指令
    mov eax, offset MSG_TEST_INC
    call dispmsg

    mov eax, offset MSG_I_STR
    call dispmsg

    mov eax, offset strbuf
    call readmsg

    mov eax, offset MSG_O_STR
    call dispmsg
    mov eax, offset strbuf
    call dispmsg
    call dispcrlf

    ; 计算字符串 strbuf 长度, 使用 inc
    xor ecx, ecx
LOOP1:
    mov al, strbuf[ecx]
    test al, al
    jz END_LOOP1
    inc ecx
    jmp LOOP1
END_LOOP1:
    mov eax, offset MSG_LEN
    call dispmsg
    mov eax, ecx
    call dispuid
    call dispcrlf

    ; 测试 dec 指令
    mov eax, offset MSG_TEST_DEC
    call dispmsg

    ; 从后向前遍历字符串 strbuf, 使用 dec
    lea esi, strbuf[ecx - 1]    ; ecx 保存有 strbuf 长度
LOOP2:
    mov al, byte ptr [esi]
    call dispc
    cmp esi, offset strbuf
    jz END_LOOP2
    mov al, '|'
    call dispc
    dec esi
    jmp LOOP2
END_LOOP2:
    call dispcrlf

    ; 测试 neg 指令
    mov eax, offset MSG_TEST_NEG
    call dispmsg

    mov eax, offset MSG_I_HEX
    call dispmsg
    call readhb
    mov bl, al
    call dispcrlf
    mov eax, offset MSG_O_BIN
    call dispmsg
    mov al, bl
    call dispbb
    mov eax, offset MSG_SIGNED_DEC
    call dispmsg
    mov al, bl
    call dispsib

    call dispcrlf
    mov eax, offset MSG_O_NEGBIN
    call dispmsg
    neg bl
    mov al, bl
    call dispbb
    mov eax, offset MSG_SIGNED_DEC
    call dispmsg
    mov al, bl
    call dispsib

    ; 程序结束提示
    call dispcrlf
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

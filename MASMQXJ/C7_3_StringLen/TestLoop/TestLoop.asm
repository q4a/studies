; TestLoop.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_STRLEN byte '----- test string len -----', 0Dh, 0Ah, 0
    MSG_RES byte 'Len: ', 0

    strbuf byte 'How do you turn this on?', 0

.code
; [in] eax
displen proc
    push ebp
    mov ebx, eax
    mov eax, offset MSG_RES
    call dispmsg
    mov eax, ebx
    call dispuid
    pop ebp
    ret
displen endp

start:
    ; ���� 0 ��β�ַ����ĳ���
    mov eax, offset MSG_TEST_STRLEN
    call dispmsg

    xor esi, esi
L1:
    mov al, strbuf[esi]
    test al, al
    jz L2
    inc esi
    jmp L1
L2:
    mov eax, esi

    call displen
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

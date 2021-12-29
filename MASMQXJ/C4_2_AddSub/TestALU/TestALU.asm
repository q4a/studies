; TestALU.asm
;

; .686, .model flat, stdcall
; IO �ӳ�������
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
    ; ���� add ָ��
    mov eax, offset MSG_TEST_ADD
    call dispmsg
    mov eax, 0AAFF7348H
    add al, 27H         ; 8bit �ӷ�
    call disprf
    call disphb
    call dispcrlf

    add ax, 3FFFH       ; 16bit �ӷ�
    call disprf
    call disphw
    call dispcrlf

    add eax, 88000000H   ; 32bit �ӷ�
    call disprf
    call disphd
    call dispcrlf

    ; ���� sub ָ��
    mov eax, offset MSG_TEST_SUB
    call dispmsg
    mov eax, 0AAFF7348H
    sub al, 27H         ; 8bit ����
    call disprf
    call disphb
    call dispcrlf

    sub ax, 3FFFH       ; 16bit ����
    call disprf
    call disphw
    call dispcrlf

    sub eax, 0BB000000H ; 32bit ����
    call disprf
    call disphd
    call dispcrlf

    ; ���Դ�Сд��ĸת��
    mov eax, offset MSG_TEST_CASECONVERT
    call dispmsg

    ; ��д��ĸת��ΪСд, ʹ�� add
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

    ; Сд��ĸת��Ϊ��д, ʹ�� sub
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

    ; ���������ʾ
    call dispcrlf
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

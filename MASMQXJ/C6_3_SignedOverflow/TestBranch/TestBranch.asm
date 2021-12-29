; TestBranch.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_OF     byte '----- test singed overflow -----', 0Dh, 0Ah, 0
    MSG_RES byte 'Res: ', 0
    MSG_OF  byte 'Error: Overflow', 0

    ; 32bit �з�������ȡֵ��Χ [�C2147483648, 2147483647]
    dvar1 dword 2147483600
    dvar2 dword -48

.code
start:
    mov eax, offset MSG_TEST_OF
    call dispmsg

    ; ʹ��˫��֧�ṹ,  �ж��з����������Ƿ����
    mov eax, dvar1
    sub eax, dvar2
    jo ERR_OF

    ; �����ʱ
    mov ebx, eax
    mov eax, offset MSG_RES
    call dispmsg
    mov eax, ebx
    call dispsid
    jmp CALC_END
ERR_OF:
    ; ���ʱ
    mov eax, offset MSG_OF
    call dispmsg
CALC_END:
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

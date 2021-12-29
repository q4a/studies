; TestBranch.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_MSB        byte '----- test MSB -----', 0Dh, 0Ah, 0

    dvar dword 80000000h

.code
start:
    mov eax, offset MSG_TEST_MSB
    call dispmsg

    ; ʹ��˫��֧�ṹ, ��ʾ���ݵ����λ MSB (Most Significant Bit)
    mov ebx, dvar
    shl ebx, 1      ; MSB ���� CF
    jc MSB_1        ; CF = 1 ��ת
    mov al, '0'     ; CF = 0 ʱ, ˳��ִ�е�����
    jmp SHOW
MSB_1:
    mov al, '1'
SHOW:
    call dispc
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

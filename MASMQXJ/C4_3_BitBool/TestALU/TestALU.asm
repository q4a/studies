; TestALU.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_XOR byte '----- test xor -----', 0Dh, 0Ah, 0
    MSG_XOR             byte 'xor: ', 0
    MSG_XOR_EQU         byte 'xor-equ: ', 0

    MSG_TEST_CASECONVERT byte '----- test char case convert -----', 0Dh, 0Ah, 0
    MSG_I_UPPER byte 'Enter an uppercase char: ', 0
    MSG_O_LOWER byte 'Lowercase char: ', 0
    MSG_I_LOWER byte 'Enter an lowercase char: ', 0
    MSG_O_UPPER byte 'Uppercase char: ', 0

    msg_operand byte 'operand '
    operand_num byte ?
                byte ': ', 0

    var_a   dword 11001010000111100101010101001101b
    var_b   dword 00110111010110100011010111100001b

.code
start:
    mov [operand_num], '1'
    mov eax, offset msg_operand
    call dispmsg
    mov eax, [var_a]
    call dispbd
    call dispcrlf
    mov [operand_num], '2'
    mov eax, offset msg_operand
    call dispmsg
    mov eax, [var_b]
    call dispbd
    call dispcrlf

    ; ���� xor ָ��
    mov eax, offset MSG_TEST_XOR
    call dispmsg
    mov eax, offset MSG_XOR
    call dispmsg
    mov eax, [var_a]
    xor eax, [var_b]
    call dispbd
    call dispcrlf

    ; ���� xor �ȼ�ָ������ A ^ B = ~A & B | A & ~B
    mov eax, offset MSG_XOR_EQU
    call dispmsg

    mov eax, [var_a]
    not eax
    and eax, [var_b]
    mov ebx, [var_b]
    not ebx
    and ebx, [var_a]
    or eax, ebx

    call dispbd
    call dispcrlf

    ; ���Դ�Сд��ĸת��
    mov eax, offset MSG_TEST_CASECONVERT
    call dispmsg

    ; ��д��ĸת��ΪСд, ʹ�� or
    mov eax, offset MSG_I_UPPER
    call dispmsg
    call readc
    mov bl, al
    call dispcrlf
    mov eax, offset MSG_O_LOWER
    call dispmsg
    mov al, bl
    or al, 20h
    call dispc
    call dispcrlf

    ; Сд��ĸת��Ϊ��д, ʹ�� and
    mov eax, offset MSG_I_LOWER
    call dispmsg
    call readc
    mov bl, al
    call dispcrlf
    mov eax, offset MSG_O_UPPER
    call dispmsg
    mov al, bl
    and al, 0DFh
    call dispc

    ; ���������ʾ
    call dispcrlf
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

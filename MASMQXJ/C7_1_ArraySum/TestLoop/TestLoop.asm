; TestLoop.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_ARRSUM byte '----- test array sum -----', 0Dh, 0Ah, 0
    MSG_RES byte 'Sum: ', 0

    array   dword 136, -138, 133, 130, -161

.code
start:
    ; ������ͳ���
    mov eax, offset MSG_TEST_ARRSUM
    call dispmsg

    mov ecx, lengthof array
    xor eax, eax
    xor esi, esi
L1:
    add eax, array[esi * type array]
    inc esi
    loop L1

    mov ebx, eax
    mov eax, offset MSG_RES
    call dispmsg
    mov eax, ebx
    call dispsid
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

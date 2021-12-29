; TestLoop.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_ARRMAX byte '----- test array max -----', 0Dh, 0Ah, 0
    MSG_RES byte 'Max: ', 0

    array   dword -3, 0, 20, 912, -56
    ARR_LEN = lengthof array

.code
; [in] eax
dispmax proc
    push ebp
    mov ebx, eax
    mov eax, offset MSG_RES
    call dispmsg
    mov eax, ebx
    call dispsid
    pop ebp
    ret
dispmax endp

start:
    ; Ѱ�������е����ֵ
    mov eax, offset MSG_TEST_ARRMAX
    call dispmsg

    ; ���� 1. ʹ�� ecx �������� + loop ѭ��ָ��

    mov ecx, ARR_LEN - 1
    xor esi, esi
    mov eax, array[esi * type array]    ; ��ʼʱ, �ٶ���һ���������ֵ
LD1:
    inc esi
    cmp eax, array[esi * type array]
    jge LD2
    mov eax, array[esi * type array]
LD2:
    loop LD1

    call dispmax
    call dispcrlf

    ; ���� 2. ʹ�� esi �������� + jcc ��תָ��

    xor esi, esi
    mov eax, array[esi * type array]
LI1:
    inc esi
    cmp eax, array[esi * type array]
    jge LI2
    mov eax, array[esi * type array]
LI2:
    cmp esi, ARR_LEN - 1
    jb LI1

    call dispmax
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

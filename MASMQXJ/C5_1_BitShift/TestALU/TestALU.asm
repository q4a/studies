; TestALU.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_BITSHIFT   byte '----- test bit-shift -----', 0Dh, 0Ah, 0

    wvar    word 34000
    qvar    qword 1234567887654321h

.code
start:
    mov eax, offset MSG_TEST_BITSHIFT
    call dispmsg

    ; 16bit ���ݵĳ˻�Ϊ 32bit
    ; ���� 10x, ʹ�� 10x = 2x + 8x ʵ��
    xor eax, eax
    mov ax, wvar

    shl eax, 1      ; r = 2x
    mov ebx, eax
    shl eax, 2      ; r = 4r = 8x
    add eax, ebx    ; r = 2x + 8x
    call dispuid
    call dispcrlf

    ; ���� 10x, ʹ�� mul ָ��
    ; ָ�� mul src, ֻ��һ��Դ������
    ; ��һ������������Ϊ al, ax, eax
    ; �������������Ϊ ax, dx:ax, edx:eax

    ; ����� 16bit �˷�
    ; wvar = 34000d = 84D0h
    ; wvar x 10 = 340000d = 53020h ���� ax ���� 3020h, dx ���� 5h

    ; ������ 32bit �˷�
    ; �� 16bit ���ݽ�����λ��չΪ 32bit
    movzx ebx, wvar
    mov eax, 10
    mul ebx     ; r = 10x
    call dispuid
    call dispcrlf

    ; 64bit �����߼�����
    shr dword ptr qvar+4, 1
    rcr dword ptr qvar, 1
    ; 64bit ������������
    sar dword ptr qvar+4, 1
    rcr dword ptr qvar, 1
    ; 64bit �����߼�/��������
    shl dword ptr qvar, 1       ; sal �� shl ��ͬ
    rcl dword ptr qvar+4, 1

    mov eax, dword ptr qvar+4
    call disphd
    mov al, ' '
    call dispc
    mov eax, dword ptr qvar
    call disphd
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

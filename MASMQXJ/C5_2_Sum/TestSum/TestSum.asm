; TestSum.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_SUM        byte '----- test sum -----', 0Dh, 0Ah, 0

    num dword 100000
    sum qword ?     ;  ��ͽ��ռ�� 64bit

.code
start:
    mov eax, offset MSG_TEST_SUM
    call dispmsg

    ; �õȲ�������͹�ʽ�� 1 + 2 + 3 + ... + N = (N + 1) * N / 2
    mov eax, num
    add eax, 1
    mul num     ; 32bit �˻�Ϊ 64bit, ��������� edx:eax

    ; edx:eax 64bit �����߼�����ʵ�ֳ��� 2
    ; ���ﲻ�ÿ��������ЧλΪ 1 ʱ, ���������Ч���ֶ�ʧ, ����Ҫ����������
    ; ��Ϊ (N + 1) * N һ����ż��, �����Чλ�� 0
    shr edx, 1
    rcr eax, 1

    ; edx:eax ���浽���� sum
    mov dword ptr sum, eax
    mov dword ptr sum+4, edx

    mov eax, edx
    call disphd
    mov al, ' '
    call dispc
    mov eax, dword ptr sum
    call disphd
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

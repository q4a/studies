; TestAddr.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    bvar    byte    12h, 34h
    org     $+10
    array   word    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    wvar    word    5678h
    ARR_SIZE    = $-array                   ; ���ݴ� 5678h �� 1 ���ֽ��� 16H (22D)
    ARR_LEN     = ARR_SIZE / sizeof word    ; �������� (word) �Ŀ��� 0BH (11D)
    TYPE_WORD   = type word                 ; sizeof word, type word, type array �Ľ����ͬ, ���������͵� size
    TYPE_ARR    = type array
    LENOF_ARR   = lengthof array            ; �õ����� (word) �����Ŀ��� 0AH (10D), ע�ⲻ����� array ��� wvar ����
    SZOF_ARR    = sizeof array              ; �õ��������ֽ��� 14H (20D), ע�ⲻ����� array ��� wvar ����
    dvar    dword 9abcdef0h

.code
start:
    ; ����ֻ���� eax, ebx �ĵ� 16bit, ������ disprd ��ӡ���� eax, ebx �ĸ� 16bit ����ʱ�仯����ֵ
    mov al, [bvar]          ; ָ�=5B, ���� bvar �� [bvar]
    mov ah, [bvar + 1]      ; ָ�=6B, �Լ� bvar + 1 �� [bvar + 1] ������ͬ, ����ʾ����������
    mov bx, wvar[2]         ; ָ�=7B, �� C/C++ ��ͬ, �����ƫ��ʼ�����ֽ���, �����������͵Ŀ���
    mov ecx, ARR_LEN        ; ָ�=5B
    mov edx, $              ; ��ǰָ��ƫ�� $=17H (23D) + .code ���ڽ��̿ռ��еļ���λ�� (ͨ���� 00401000H)
    mov esi, offset dvar    ; esi <= dvar ��ƫ�� (22H) + .data ���ڽ��̿ռ��еļ���λ�� (ͨ���� 00405000H)
    mov edi, [esi]
    mov ebp, [dvar]
    ; mov esp, dword ptr array    ; һ�㲻Ҫֱ�Ӹ��� esp, ��������� call ָ���޷���������
    mov eax, dword ptr array

    call disprd

    exit 0
end start

; TestAddr.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    srcmsg  byte    'Try your best, why not.', 0
    dstmsg  byte    sizeof srcmsg dup(?)

.code
start:
    ; ʹ�ô洢���ļĴ������Ѱַ, �����ַ���
    mov ecx, lengthof srcmsg
    mov esi, offset srcmsg
    mov edi, offset dstmsg
again:
    mov al, [esi]
    mov [edi], al
    add esi, 1
    add edi, 1
    loop again  ; ecx �Լ� 1, �� ecx == 0 ����ѭ��

    mov eax, offset dstmsg
    call dispmsg

    exit 0
end start

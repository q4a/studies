; Hello.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.data
    msg byte 'Hello Assembly!', 0Dh, 0Ah, 0 ; �����ַ���. 0Dh, 0Ah, 0 ������ CR LF \0

.code
start:
    mov eax, offset msg                     ; �����ӳ��� dispmsg ��ʾ
    call dispmsg

    exit 0
end start

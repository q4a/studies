; TestProc.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.const
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_BANNER     byte '----- test procedure -----', 0Dh, 0Ah, 0

.code

modRetAddr proc
    push ebp
    mov ebp, esp
    mov eax, offset L2  ; L2 ���������еı��
    mov [ebp + 4], eax  ; �޸� [���ص�ַ]
    leave
    ret
modRetAddr endp

mydispcrlf proc
    ; ���ݵ���Լ������Ҫ, ������Ӧ�ļĴ�����ֵ
    ; ���� MSVC x86 (32bit) __cdecl (C ����) �� __stdcall ����Լ��:
    ; EAX, ECX, EDX �� caller-saved �Ĵ���
    ; EBX, ESI, EDI �� callee-saved �Ĵ���

    ; �ù���û�д������ �� �ֲ�����, ����û��ʹ�� prolog/epilog ����ջ֡ (stack frame)
    mov al, 0Dh
    call dispc
    mov al, 0Ah
    call dispc
    ret
mydispcrlf endp

; �������
start:
    mov eax, offset MSG_TEST_BANNER
    call dispmsg

    call Next   ; �� [���ص�ַ] Next ѹջ
Next: pop eax   ; eax �õ� pop eax ����ָ��ĵ�ַ Next
    call disphd
    call mydispcrlf

    call modRetAddr
L1: mov eax, 1  ; modRetAddr ���޸��� [���ص�ַ], ���� L1~L2 ֮���ָ���ִ��
    call dispuid
L2: mov eax, 4
    call dispuid
    call dispcrlf

    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

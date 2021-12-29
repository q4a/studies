; TestExpr.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.const
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_BANNER     byte '----- test expression evaluation -----', 0Dh, 0Ah, 0
    MSG_INPUT_ERR       byte 'Require a number > 7', 0Dh, 0Ah, 0
    MSG_INPUT_PROMPT    byte 'Input a number > 7:', 0Dh, 0Ah, 0
    MSG_EVAL_EXPR       byte '(var1 * 6) / (var2 - 7) + var3 = ', 0

    PROMPT_DELIM        byte '> ', 0

.data
    BUF_SIZE            = 64
    promptBuf           byte (BUF_SIZE - 1) dup(?), 0

    varname             byte 'var', ?, 0
    VARNAME_OFFSET      = 3
    var                 dword 4 dup(?)
    VARSZ               = type var

.code

showesp macro
    push eax
    mov eax, esp
    call disphd
    call dispcrlf
    pop eax
endm

; �ڿ���̨��ʾ������, ���Ӽ���������������ֵ
; [in] vn   �������ַ���
; [in] len  �������ַ����ĳ���, ��������β 0
;
; �� proc �����в����б� vn:dword, len:dword ʱ, ���Զ����� prolog/epilog:
; 1. prolog: push ebp, mov ebp, esp
; 2. epilog: leave, �ȼ��� mov esp, ebp; pop ebp
; 3. �� stdcall ����Լ��ʱ, MASM ������������ ret ָ���Զ�ת��Ϊ�������� ret n ָ��, n Ϊ�����Ĳ����ֽ���
; ������:
; һ��ɾ�������б�, ��ʹ���� proto stdcall ����Լ��˵��, Ҳ�����Զ��������� prolog/epilog, �Ҳ��Ὣ ret �Զ�ת��Ϊ ret n
;
; �鿴��Щ���� [����Լ��˵��] �� [�����б�] �Զ����ɵ� prolog/epilog:
; .lst �в���������Щ�Զ����ɵ�ָ��, ���Զ�Ŀ���ļ��� dumpbin /disasm file.obj �����ת����ӡ
; ����, �ú������������ prolog/epilog
; _inputVar@8:                          ; ���ɷ��� MSVC __stdcall ����Լ����������
; 00000000: 55          push    ebp     ; ǰ�������Զ����ɵ�
; 00000001: 8B EC       mov     ebp,esp
; 00000003: 56          push    esi     ; ���������ֹ�д��
; 00000004: 57          push    edi
; ...
; 0000003F: 5F          pop     edi     ; ǰ�������ֹ�д��
; 00000040: 5E          pop     esi
; 00000041: C9          leave           ; ���������Զ����ɵ�
; 00000042: C2 08 00    ret 8           ; ����������Ǵ������� ret n [opcode: C2], �����ǲ��������� ret [opcode: C3]
inputVar proto stdcall :dword, :dword
inputVar proc vn:dword, len:dword
    push esi
    push edi

    ; ���Ʊ������������� promptBuf
    mov ecx, len    ; len = [ebp + 12]
    mov esi, vn     ; vn = [ebp + 8]
    mov edi, offset promptBuf
    cld
    rep movsb

    ; ������ʾ�� > �������� promptBuf
    mov ecx, lengthof PROMPT_DELIM
    mov esi, offset PROMPT_DELIM
    rep movsb

@@:
    mov eax, offset promptBuf
    call dispmsg
    call readuid

    ; ��֤������� > 7
    cmp eax, 7
    ja GO
    mov eax, offset MSG_INPUT_ERR
    call dispmsg
    jmp @B

GO:
    pop edi
    pop esi
    ; ��Ϊ���� stdcall, �����ɱ������������ջ
    ; ��Ϊ�ù��̴������б�, �����������д ret 8, Ҳ����д ret, MASM �Ὣ�����Զ�ת��Ϊǰ��
    ret
inputVar endp

; ����ʽ var4 = (var1 * 6) / (var2 - 7) + var3 ��ֵ
; �� var1 ~ var4 ������ȫ�����鵥Ԫ var[0] ~ var[3] ��, ��ֵΪ�� > 7 �� unsigned long
; ���̷��� var4 ��ֵ
evalExpr proto stdcall
evalExpr proc
    push ebp
    mov ebp, esp
    push ebx

    mov eax, var[0]
    shl eax, 1                  ; var1 * 2
    lea eax, [eax + eax * 2]    ; var1 * 6 = (var1 * 2) + (var1 * 2) * 2

    mov ebx, var[1 * VARSZ]
    sub ebx, 7                  ; var2 - 7

    xor edx, edx
    div ebx                     ; (var1 * 6) / (var2 - 7), ����������Ϊ edx:eax, ������Ϊ eax

    mov ebx, var[2 * VARSZ]
    add eax, ebx                ; (var1 * 6) / (var2 - 7) + var3

    mov var[3 * VARSZ], eax     ; ���浽 var4

    pop ebx
    leave
    ret
evalExpr endp

; �������
start:
    mov eax, offset MSG_TEST_BANNER
    call dispmsg

    mov eax, offset MSG_INPUT_PROMPT
    call dispmsg
    ; ���� var �ı����� var1 ~ var4, ��Ӧ���鵥Ԫ var[0] ~ var[3]
    ; ����ʹ�� bl (ebx), ����Ϊ��ѭ�����жԹ��� inputVar �ĵ���
    ; ���� stdcall ����Լ��, eax, ecx, edx �� caller-saved �Ĵ���, �� ebx �� callee-saved �Ĵ���
    ; ʹ�� ebx ����������̵���ǰ�ԼĴ����ı���
    xor ebx, ebx
@@:
    mov al, bl
    add al, '1'     ; ������ (0~3) ת��Ϊ�ַ� (1~4)
    mov varname[VARNAME_OFFSET], al

    ; showesp
    ; invoke �ȼ���������ָ��
    ; push 4
    ; push offset varname
    ; call inputVar
    invoke inputVar, offset varname, 4
    ; showesp   ; ����ջ�Ƿ�ƽ��
    mov var[ebx * VARSZ], eax

    inc bl
    cmp bl, 4
    jnz @B

    call dispcrlf

    ; ��� var[0] ~ var[3]
    xor ebx, ebx
@@:
    mov al, bl
    add al, '1'
    mov varname[VARNAME_OFFSET], al

    mov eax, offset varname
    call dispmsg
    mov al, '='
    call dispc

    mov eax, var[ebx * VARSZ]
    call dispuid
    call dispcrlf
    inc bl
    cmp bl, 4
    jnz @B

    call evalExpr
    mov eax, offset MSG_EVAL_EXPR
    call dispmsg
    mov eax, var[3 * VARSZ]
    call dispuid

    call dispcrlf
    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

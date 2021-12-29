; TestProc.asm
;

; IO �ӳ�������
; .686, .model flat, stdcall
include io32.inc

.const
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_BANNER     byte '----- test procedure param-passing -----', 0Dh, 0Ah, 0
    MSG_INPUT_BIN       byte 'Input a 32bit binary> ', 0

.data
    Data                dword 6789ABCDh
    Asc                 byte 8 dup(?), 0

    COUNT               = 2
    Array               dword COUNT dup(?)
    Temp                dword ?

    Array2              dword 675, 354, -34, 198, 267, 9, 2371, -67, 4257

.code

; [in] al   �� al �ĵ� 4bit ת��Ϊ��ʾ����ʮ������ ASCII �� (0~F)
htoasc proc
    and al, 0Fh     ; ��ȡ�� 4bit
    or al, 30h      ; ����ֵ 0~9 ת��Ϊ ASCII ��
    cmp al, 39h     ; ��������� 0~9, ˵��ԭ��ֵ�� A~F, ����� 7
    jbe @F
    add al, 7
@@:
    ret
htoasc endp

; htoasc �Ĳ��ʵ�ַ���
htoasc2 proc
    and eax, 0Fh                ; ��ȡ�� 4bit
    mov al, ASCII[eax]
    ret

; �����ݲ����� .code ����� (ֻ��), �ǹ������һ����
; ��˽������ ret ָ��֮��, �Է�ֹ������Ϊָ��ִ��
ASCII   byte '0123456789ABCDEF'
htoasc2 endp

; ����: ͨ���Ĵ������ݲ���
; [in] procHtoasc       ָ�� htoasc ���̵�ָ��
testHextoAsc proc procHtoasc:dword
    push ebx
    push esi

    mov eax, [Data]
    xor esi, esi
@@:
    rol eax, 4      ; �� 4bit ѭ����λ����� 4bit
    mov ebx, eax    ; ���� eax
    call procHtoasc
    mov Asc[esi], al
    mov eax, ebx    ; ��ԭ eax
    inc esi
    cmp esi, 8
    jnz @B

    mov eax, offset Asc
    call dispmsg

    pop esi
    pop ebx
    ret 4
testHextoAsc endp

; �ӿ���̨���� 32bit ��������
rdbd proc
L1:
    xor edx, edx
    mov ecx, 32
@@:
    call readc
    cmp al, '0'
    jb ERR
    cmp al, '1'
    ja ERR

    and al, 0Fh     ; �� ASCII �� 0, 1 ת��Ϊ��ֵ
    shl edx, 1      ; �ϲ�֮ǰ����Ľ��
    or dl, al       ; ֻ�úϲ��� 8bit
    loop @B

    mov [Temp], edx
    call dispcrlf
    ret

ERR:
    mov eax, offset ERRMSG
    call dispmsg
    mov eax, offset MSG_INPUT_BIN
    call dispmsg
    jmp L1
ERRMSG  byte 0Dh, 0Ah, 'Input error, enter again.', 0Dh, 0Ah, 0
rdbd endp

; ����: ͨ��ȫ�ֹ���������ݲ���
testGlobal proc
    push ebp
    mov ebp, esp
    push ebx
    push esi

    mov ecx, COUNT
    mov esi, offset Array
@@:
    mov eax, offset MSG_INPUT_BIN
    call dispmsg
    mov ebx, ecx    ; ���� ecx
    call rdbd
    mov eax, [Temp]
    mov [esi], eax
    mov ecx, ebx    ; ��ԭ ecx
    add esi, type Array
    loop @B

    mov ecx, COUNT
    mov esi, offset Array
@@:
    mov ebx, ecx    ; ���� ecx
    mov eax, [esi]
    call dispbd
    call dispcrlf
    mov ecx, ebx    ; ��ԭ ecx
    add esi, type Array
    loop @B

    pop esi
    pop ebx
    leave
    ret
testGlobal endp

; �� DWORD �������� arr ������Ԫ�ص�ƽ��ֵ
; �� proc ���в����б�ʱ, �Զ����� prolog (push ebp; mov ebp, esp) �� epilog (leave)
; �Լ������������� ret ָ���Զ�ת��Ϊ�������� ret n ָ��
mean proc arr:dword, len:dword
    push ebx
    push esi

    mov ebx, arr    ; arr = [ebp + 8]
    mov ecx, len    ; len = [ebp + 12]
    xor eax, eax
    jecxz GO
    xor esi, esi
@@:
    add eax, [ebx + esi * type dword]
    inc esi
    cmp esi, ecx
    jb @B           ; ���ﲻ�� loop ָ��, ��Ϊ loop ���Լ� ecx, ������Ҫ�õ� ecx

    ; �� eax ������չ�� edx:eax
    ; �ȼ��� mov edx, eax; sar edx, 31
    cdq
    idiv ecx
GO:
    pop esi
    pop ebx
    ret             ; ����д ret 8 �� ret ������, MASM �������Զ�ת��Ϊǰ��
mean endp

; ����: ͨ����ջ���ݲ���
testMean proc
    push ebp
    mov ebp, esp
    push ebx

    ; ��ӡ����ǰ�� esp
    ; mov eax, esp
    ; call disphd
    ; call dispcrlf

    ; ���� invoke �ȼ���������ָ��
    ; push lengthof Array2
    ; push offset Array2
    ; call mean
    invoke mean, offset Array2, lengthof Array2

    ; ��ӡ���ú�� esp, ��֤��ջ�Ƿ��ѱ�����
    ; mov ebx, eax
    ; mov eax, esp
    ; call disphd
    ; call dispcrlf
    ; mov eax, ebx

    call dispsid

    pop ebx
    leave
    ret
testMean endp

; �������
start:
    mov eax, offset MSG_TEST_BANNER
    call dispmsg

    invoke testHextoAsc, htoasc
    call dispcrlf
    invoke testHextoAsc, htoasc2
    call dispcrlf

    call testGlobal
    call testMean

    call dispcrlf
    ; ���������ʾ
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

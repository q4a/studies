; Euclid.asm
;

ifndef __WIN64__
.686
.model flat, c
endif
option casemap:none

; ���� .asm �Ĺ�������
;
; �� .asm ������ҳ
; 1. ���Ƚ� General �е� Tool ����Ϊ Custom Build Tool
; 2. Ȼ���� Custom Build Step > General ������ Command Line:
; Debug/Release ���þ����ɺ�������Ϣ (/Zi) ��Ŀ���ļ�
; x86 (32bit):
; ml /nologo /c /Zi /Fl"$(IntDir)\$(InputName).lst" /FR"$(IntDir)\$(InputName).sbr" /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"
; x64 (64bit):
; ml64 /nologo /c /Zi /D"__WIN64__" /Fl"$(IntDir)\$(InputName).lst" /FR"$(IntDir)\$(InputName).sbr" /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"
;
; ���� Outputs:
; $(IntDir)\$(InputName).obj
; $(IntDir)\$(InputName).sbr    [�������Ҫ�� /FR ���� Source Browser Information (.sbr), ����������ļ�]
;
; ���� ml ����������м�Ŀ¼ $(IntDir) ����:
; 1. Object File (.obj)
; 2. Assembled Code Listing (.lst)
; 3. Source Browser Information (.sbr)
;
; ���� Source Browser Information (.sbr) �� VS �� Object Browser
; �� VS IDE �й���ʱ, ���Զ����� bscmake ���м�Ŀ¼�е� .sbr ת��Ϊ���Ŀ¼ $(OutDir) �е� .bsc
; �� .bsc �Ϸŵ� VS IDE ���Դ� Object Browser, �ɲ鿴 .bsc �еķ��Ų���ת����ӦԴ��λ��
; ��ִ���� .sbr �� .bsc ���Զ�ת����, .sbr ���ɿ��ļ�
; ��ʱ .sbr �� .bsc ���Զ�ת��, ����ı乹�������ͻȻ����������, ��ʹ�Ļ�ԭ�ȵĹ�������Ҳ��������
; ��ʱ�ر� VS ��ɾ�����������ļ��������ܽ��
; .sbr/.bsc ����ϻ���������ʱ, û�� .lst ��Ҫ, ����һ�㲻������ .sbr

.code

; MASM x86 �� x64 ����ֲ����:
; 1. MASM x64 ����� (ml64) ��֧��ָʾ .386, .model flat, c
; 2. MSVC x64 Ĭ��ʹ�� x64 fastcall ����Լ��, �� MSVC x86 Ĭ��ʹ�� __cdecl ����Լ��
;    MSVC x64 ���ܵ����� MSVC x86 �ĵ���Լ���ؼ��� __cdecl, __stdcall, __fastcall
;    __cdecl �� x64 fastcall �ڲ��������ϵ����������:
;    __cdecl ʹ��ջ����ȫ������
;    x64 fastcall ʹ�� RCX, RDX, R8, R9 ����ǰ 4 �������� QWORD ��С�Ĳ���, ʣ�����ʹ��ջ����
;
; ���ֽ������:
; 1. Ϊ x86, x64 �ֱ��д���� .asm ������
; 2. �����������, ���� __cdecl �� x64 fastcall ���ֵ���Լ��, �Լ� MASM x86/x64 ֮��Ĳ���
;
; �ο�:
; x64 software conventions
; https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions
; .MODEL
; https://docs.microsoft.com/en-us/cpp/assembler/masm/dot-model
; ��������������ʾ��

; ʹ��ŷ������㷨 (Euclid's Algorithm) �����Լ��:
; Repeatedly subtracting the smaller number from the larger number until zero is reached.
; The number remaining is the greatest common divisor.
ifdef __WIN64__
; MASM x64 �в�Ҫ���������б�, ������� MASM x86 һ���Զ����ɽ���/����ջ֡�� prolog/epilog �Ĵ���
; ��Ȼ�� MASM x64 ������ջ֡��û�д���, ������ֻ�� [�������� + ��С������] �ĺ�������ȴ�ǲ���Ҫ��
Euclid proc
    mov eax, edx
else
; MASM x86
Euclid proc x:sdword, y:sdword
    mov ecx, x
    mov eax, y
endif
@@:
    cmp ecx, eax
    jge NOSWAP
    xchg eax, ecx
NOSWAP:
    sub ecx, eax
    jnz @B
    ; ���Լ����������Ϊ����ֵ�� eax ��
    ret
Euclid endp

end

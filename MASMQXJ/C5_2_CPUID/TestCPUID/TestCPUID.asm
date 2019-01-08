; TestCPUID.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_CPUID      byte '----- test cpuid -----', 0Dh, 0Ah, 0

    VENDORID_SIZE   = 12
    msgbuf byte 'CPU vendor: ', VENDORID_SIZE dup(?), 0
    BUF_SIZE = sizeof msgbuf
    VENDORID_OFFSET = BUF_SIZE - VENDORID_SIZE - 1

.code
start:
    mov eax, offset MSG_TEST_CPUID
    call dispmsg

    ; 用 cpuid 指令取得 CPU vendor 标识
    ; Intel: GenuineIntel
    ; AMD: AuthenticAMD
    xor eax, eax
    cpuid

    mov dword ptr msgbuf[VENDORID_OFFSET], ebx
    mov dword ptr msgbuf[VENDORID_OFFSET + 4], edx
    mov dword ptr msgbuf[VENDORID_OFFSET + 8], ecx
    mov eax, offset msgbuf
    call dispmsg
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

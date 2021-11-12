; TestSum.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_SUM        byte '----- test sum -----', 0Dh, 0Ah, 0

    num dword 100000
    sum qword ?     ;  求和结果占用 64bit

.code
start:
    mov eax, offset MSG_TEST_SUM
    call dispmsg

    ; 用等差数列求和公式求 1 + 2 + 3 + ... + N = (N + 1) * N / 2
    mov eax, num
    add eax, 1
    mul num     ; 32bit 乘积为 64bit, 结果保存在 edx:eax

    ; edx:eax 64bit 整体逻辑右移实现除以 2
    ; 这里不用考虑最低有效位为 1 时, 右移造成有效数字丢失, 而需要修正的问题
    ; 因为 (N + 1) * N 一定是偶数, 最低有效位是 0
    shr edx, 1
    rcr eax, 1

    ; edx:eax 保存到变量 sum
    mov dword ptr sum, eax
    mov dword ptr sum+4, edx

    mov eax, edx
    call disphd
    mov al, ' '
    call dispc
    mov eax, dword ptr sum
    call disphd
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

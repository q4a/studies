; TestLoop.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT byte 'Press any key to Exit...', 0
    MSG_TEST_ARRMAX byte '----- test array max -----', 0Dh, 0Ah, 0
    MSG_RES byte 'Max: ', 0

    array   dword -3, 0, 20, 912, -56
    ARR_LEN = lengthof array

.code
; [in] eax
dispmax proc
    push ebp
    mov ebx, eax
    mov eax, offset MSG_RES
    call dispmsg
    mov eax, ebx
    call dispsid
    pop ebp
    ret
dispmax endp

start:
    ; 寻找数组中的最大值
    mov eax, offset MSG_TEST_ARRMAX
    call dispmsg

    ; 方法 1. 使用 ecx 减量计数 + loop 循环指令

    mov ecx, ARR_LEN - 1
    xor esi, esi
    mov eax, array[esi * type array]    ; 初始时, 假定第一个数是最大值
LD1:
    inc esi
    cmp eax, array[esi * type array]
    jge LD2
    mov eax, array[esi * type array]
LD2:
    loop LD1

    call dispmax
    call dispcrlf

    ; 方法 2. 使用 esi 增量计数 + jcc 跳转指令

    xor esi, esi
    mov eax, array[esi * type array]
LI1:
    inc esi
    cmp eax, array[esi * type array]
    jge LI2
    mov eax, array[esi * type array]
LI2:
    cmp esi, ARR_LEN - 1
    jb LI1

    call dispmax
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

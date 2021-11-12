; TestALU.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_BITSHIFT   byte '----- test bit-shift -----', 0Dh, 0Ah, 0

    wvar    word 34000
    qvar    qword 1234567887654321h

.code
start:
    mov eax, offset MSG_TEST_BITSHIFT
    call dispmsg

    ; 16bit 数据的乘积为 32bit
    ; 计算 10x, 使用 10x = 2x + 8x 实现
    xor eax, eax
    mov ax, wvar

    shl eax, 1      ; r = 2x
    mov ebx, eax
    shl eax, 2      ; r = 4r = 8x
    add eax, ebx    ; r = 2x + 8x
    call dispuid
    call dispcrlf

    ; 计算 10x, 使用 mul 指令
    ; 指令 mul src, 只有一个源操作数
    ; 另一个操作数隐含为 al, ax, eax
    ; 结果操作数隐含为 ax, dx:ax, edx:eax

    ; 如果做 16bit 乘法
    ; wvar = 34000d = 84D0h
    ; wvar x 10 = 340000d = 53020h 其中 ax 保存 3020h, dx 保存 5h

    ; 这里做 32bit 乘法
    ; 将 16bit 数据进行零位扩展为 32bit
    movzx ebx, wvar
    mov eax, 10
    mul ebx     ; r = 10x
    call dispuid
    call dispcrlf

    ; 64bit 数据逻辑右移
    shr dword ptr qvar+4, 1
    rcr dword ptr qvar, 1
    ; 64bit 数据算术右移
    sar dword ptr qvar+4, 1
    rcr dword ptr qvar, 1
    ; 64bit 数据逻辑/算术左移
    shl dword ptr qvar, 1       ; sal 和 shl 相同
    rcl dword ptr qvar+4, 1

    mov eax, dword ptr qvar+4
    call disphd
    mov al, ' '
    call dispc
    mov eax, dword ptr qvar
    call disphd
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

; TestAddr.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    bvar    byte    12h, 34h
    org     $+10
    array   word    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    wvar    word    5678h
    ARR_SIZE    = $-array                   ; 内容从 5678h 到 1 的字节数 16H (22D)
    ARR_LEN     = ARR_SIZE / sizeof word    ; 数据类型 (word) 的块数 0BH (11D)
    TYPE_WORD   = type word                 ; sizeof word, type word, type array 的结果相同, 都返回类型的 size
    TYPE_ARR    = type array
    LENOF_ARR   = lengthof array            ; 得到类型 (word) 变量的块数 0AH (10D), 注意不会计算 array 后的 wvar 部分
    SZOF_ARR    = sizeof array              ; 得到变量的字节数 14H (20D), 注意不会计算 array 后的 wvar 部分
    dvar    dword 9abcdef0h

.code
start:
    ; 这里只操作 eax, ebx 的低 16bit, 所以用 disprd 打印出的 eax, ebx 的高 16bit 是随时变化的脏值
    mov al, [bvar]          ; 指令长=5B, 这里 bvar 和 [bvar]
    mov ah, [bvar + 1]      ; 指令长=6B, 以及 bvar + 1 和 [bvar + 1] 意义相同, 都表示变量的内容
    mov bx, wvar[2]         ; 指令长=7B, 与 C/C++ 不同, 这里的偏移始终是字节数, 而非数据类型的块数
    mov ecx, ARR_LEN        ; 指令长=5B
    mov edx, $              ; 当前指令偏移 $=17H (23D) + .code 段在进程空间中的加载位置 (通常是 00401000H)
    mov esi, offset dvar    ; esi <= dvar 的偏移 (22H) + .data 段在进程空间中的加载位置 (通常是 00405000H)
    mov edi, [esi]
    mov ebp, [dvar]
    ; mov esp, dword ptr array    ; 一般不要直接更改 esp, 会引起后续 call 指令无法正常工作
    mov eax, dword ptr array

    call disprd

    exit 0
end start

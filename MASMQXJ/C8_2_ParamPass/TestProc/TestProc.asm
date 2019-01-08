; TestProc.asm
;

; IO 子程序声明
; .686
; .model flat, stdcall
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

; [in] al   将 al 的低 4bit 转换为表示它的十六进制 ASCII 码 (0~F)
htoasc proc
    and al, 0Fh     ; 析取低 4bit
    or al, 30h      ; 将数值 0~9 转换为 ASCII 码
    cmp al, 39h     ; 如果超出了 0~9, 说明原数值是 A~F, 还需加 7
    jbe @F
    add al, 7
@@:
    ret
htoasc endp

; htoasc 的查表实现方法
htoasc2 proc
    and eax, 0Fh                ; 析取低 4bit
    mov al, ASCII[eax]
    ret

; 该数据产生在 .code 代码段 (只读), 是过程体的一部分
; 因此将其放在 ret 指令之后, 以防止将其作为指令执行
ASCII   byte '0123456789ABCDEF'
htoasc2 endp

; 测试: 通过寄存器传递参数
; [in] procHtoasc       指向 htoasc 过程的指针
testHextoAsc proc procHtoasc:dword
    push ebx
    push esi

    mov eax, [Data]
    xor esi, esi
@@:
    rol eax, 4      ; 高 4bit 循环移位进入低 4bit
    mov ebx, eax    ; 保存 eax
    call procHtoasc
    mov Asc[esi], al
    mov eax, ebx    ; 还原 eax
    inc esi
    cmp esi, 8
    jnz @B

    mov eax, offset Asc
    call dispmsg

    pop esi
    pop ebx
    ret 4
testHextoAsc endp

; 从控制台输入 32bit 二进制数
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

    and al, 0Fh     ; 将 ASCII 码 0, 1 转换为数值
    shl edx, 1      ; 合并之前输入的结果
    or dl, al       ; 只用合并低 8bit
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

; 测试: 通过全局共享变量传递参数
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
    mov ebx, ecx    ; 保存 ecx
    call rdbd
    mov eax, [Temp]
    mov [esi], eax
    mov ecx, ebx    ; 还原 ecx
    add esi, type Array
    loop @B

    mov ecx, COUNT
    mov esi, offset Array
@@:
    mov ebx, ecx    ; 保存 ecx
    mov eax, [esi]
    call dispbd
    call dispcrlf
    mov ecx, ebx    ; 还原 ecx
    add esi, type Array
    loop @B

    pop esi
    pop ebx
    leave
    ret
testGlobal endp

; 求 DWORD 整数数组 arr 中所有元素的平均值
; 当 proc 后有参数列表时, 自动产生 prolog (push ebp; mov ebp, esp) 和 epilog (leave)
; 以及将不带参数的 ret 指令自动转换为带参数的 ret n 指令
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
    jb @B           ; 这里不用 loop 指令, 因为 loop 会自减 ecx, 而下面要用到 ecx

    ; 将 eax 符号扩展到 edx:eax
    ; 等价于 mov edx, eax; sar edx, 31
    cdq
    idiv ecx
GO:
    pop esi
    pop ebx
    ret             ; 这里写 ret 8 和 ret 都可以, MASM 将后者自动转换为前者
mean endp

; 测试: 通过堆栈传递参数
testMean proc
    push ebp
    mov ebp, esp
    push ebx

    ; 打印调用前的 esp
    ; mov eax, esp
    ; call disphd
    ; call dispcrlf

    ; 以下 invoke 等价于这三条指令
    ; push lengthof Array2
    ; push offset Array2
    ; call mean
    invoke mean, offset Array2, lengthof Array2

    ; 打印调用后的 esp, 验证堆栈是否已被清理
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

; 程序入口
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
    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

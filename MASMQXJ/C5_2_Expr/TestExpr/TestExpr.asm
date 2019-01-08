; TestExpr.asm
;

; IO 子程序声明
; .686
; .model flat, stdcall
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

; 在控制台提示变量名, 并从键盘输入获得其整数值
; [in] vn   变量名字符串
; [in] len  变量名字符串的长度, 不包含结尾 0
;
; 当 proc 后面有参数列表 vn:dword, len:dword 时, 会自动生成 prolog/epilog:
; 1. prolog: push ebp, mov ebp, esp
; 2. epilog: leave, 等价于 mov esp, ebp; pop ebp
; 3. 在 stdcall 调用约定时, MASM 将不带参数的 ret 指令自动转换为带参数的 ret n 指令, n 为函数的参数字节数
; 经测试:
; 一旦删除参数列表, 即使还有 proto stdcall 调用约定说明, 也不会自动生成以上 prolog/epilog, 且不会将 ret 自动转换为 ret n
;
; 查看这些根据 [调用约定说明] 和 [参数列表] 自动生成的 prolog/epilog:
; .lst 中并不包含这些自动生成的指令, 可以对目标文件用 dumpbin /disasm file.obj 反汇编转储打印
; 例如, 该函数会产生如下 prolog/epilog
; _inputVar@8:                          ; 生成符合 MSVC __stdcall 调用约定的修饰名
; 00000000: 55          push    ebp     ; 前两条是自动生成的
; 00000001: 8B EC       mov     ebp,esp
; 00000003: 56          push    esi     ; 后两条是手工写的
; 00000004: 57          push    edi
; ...
; 0000003F: 5F          pop     edi     ; 前两条是手工写的
; 00000040: 5E          pop     esi
; 00000041: C9          leave           ; 后两条是自动生成的
; 00000042: C2 08 00    ret 8           ; 这里产生的是带参数的 ret n [opcode: C2], 而不是不带参数的 ret [opcode: C3]
inputVar proto stdcall :dword, :dword
inputVar proc vn:dword, len:dword
    push esi
    push edi

    ; 复制变量名到缓冲区 promptBuf
    mov ecx, len    ; len = [ebp + 12]
    mov esi, vn     ; vn = [ebp + 8]
    mov edi, offset promptBuf
    cld
    rep movsb

    ; 复制提示符 > 到缓冲区 promptBuf
    mov ecx, lengthof PROMPT_DELIM
    mov esi, offset PROMPT_DELIM
    rep movsb

@@:
    mov eax, offset promptBuf
    call dispmsg
    call readuid

    ; 保证输入的数 > 7
    cmp eax, 7
    ja GO
    mov eax, offset MSG_INPUT_ERR
    call dispmsg
    jmp @B

GO:
    pop edi
    pop esi
    ; 因为采用 stdcall, 所以由被调用者清理堆栈
    ; 因为该过程带参数列表, 所以这里可以写 ret 8, 也可以写 ret, MASM 会将后者自动转换为前者
    ret
inputVar endp

; 求表达式 var4 = (var1 * 6) / (var2 - 7) + var3 的值
; 设 var1 ~ var4 保存在全局数组单元 var[0] ~ var[3] 中, 且值为均 > 7 的 unsigned long
; 过程返回 var4 的值
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
    div ebx                     ; (var1 * 6) / (var2 - 7), 被除数隐含为 edx:eax, 商隐含为 eax

    mov ebx, var[2 * VARSZ]
    add eax, ebx                ; (var1 * 6) / (var2 - 7) + var3

    mov var[3 * VARSZ], eax     ; 保存到 var4

    pop ebx
    leave
    ret
evalExpr endp

; 程序入口
start:
    mov eax, offset MSG_TEST_BANNER
    call dispmsg

    mov eax, offset MSG_INPUT_PROMPT
    call dispmsg
    ; 生成 var 的变量名 var1 ~ var4, 对应数组单元 var[0] ~ var[3]
    ; 这里使用 bl (ebx), 是因为在循环中有对过程 inputVar 的调用
    ; 按照 stdcall 调用约定, eax, ecx, edx 是 caller-saved 寄存器, 而 ebx 是 callee-saved 寄存器
    ; 使用 ebx 可以免除过程调用前对寄存器的保存
    xor ebx, ebx
@@:
    mov al, bl
    add al, '1'     ; 将整数 (0~3) 转换为字符 (1~4)
    mov varname[VARNAME_OFFSET], al

    ; showesp
    ; invoke 等价于这三条指令
    ; push 4
    ; push offset varname
    ; call inputVar
    invoke inputVar, offset varname, 4
    ; showesp   ; 检查堆栈是否平衡
    mov var[ebx * VARSZ], eax

    inc bl
    cmp bl, 4
    jnz @B

    call dispcrlf

    ; 输出 var[0] ~ var[3]
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
    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

; TestProc.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.const
    MSG_EXIT_PROMPT     byte 'Press any key to Exit...', 0
    MSG_TEST_BANNER     byte '----- test procedure -----', 0Dh, 0Ah, 0

.code

modRetAddr proc
    push ebp
    mov ebp, esp
    mov eax, offset L2  ; L2 是主过程中的标号
    mov [ebp + 4], eax  ; 修改 [返回地址]
    leave
    ret
modRetAddr endp

mydispcrlf proc
    ; 根据调用约定和需要, 保护相应的寄存器旧值
    ; 对于 MSVC x86 (32bit) __cdecl (C 语言) 和 __stdcall 调用约定:
    ; EAX, ECX, EDX 是 caller-saved 寄存器
    ; EBX, ESI, EDI 是 callee-saved 寄存器

    ; 该过程没有传入参数 和 局部变量, 所以没有使用 prolog/epilog 产生栈帧 (stack frame)
    mov al, 0Dh
    call dispc
    mov al, 0Ah
    call dispc
    ret
mydispcrlf endp

; 程序入口
start:
    mov eax, offset MSG_TEST_BANNER
    call dispmsg

    call Next   ; 将 [返回地址] Next 压栈
Next: pop eax   ; eax 得到 pop eax 本条指令的地址 Next
    call disphd
    call mydispcrlf

    call modRetAddr
L1: mov eax, 1  ; modRetAddr 中修改了 [返回地址], 所以 L1~L2 之间的指令不会执行
    call dispuid
L2: mov eax, 4
    call dispuid
    call dispcrlf

    ; 程序结束提示
    mov eax, offset MSG_EXIT_PROMPT
    call dispmsg
    call readc

    exit 0
end start

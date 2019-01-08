; TestAddr.asm
;

; .686, .model flat, stdcall
; IO 子程序声明
include io32.inc

.data
    srcmsg  byte    'Try your best, why not.', 0
    dstmsg  byte    sizeof srcmsg dup(?)

.code
start:
    ; 使用存储器的寄存器相对寻址, 拷贝字符串
    mov ecx, lengthof srcmsg
    mov ebx, 0
again:
    mov al, srcmsg[ebx]
    mov dstmsg[ebx], al
    add ebx, 1
    loop again  ; ecx 自减 1, 当 ecx == 0 结束循环

    mov eax, offset dstmsg
    call dispmsg

    exit 0
end start

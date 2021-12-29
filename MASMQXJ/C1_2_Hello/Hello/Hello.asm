; Hello.asm
;

; IO 子程序声明
; .686, .model flat, stdcall
include io32.inc

.data
    msg byte 'Hello Assembly!', 0Dh, 0Ah, 0 ; 定义字符串. 0Dh, 0Ah, 0 即序列 CR LF \0

.code
start:
    mov eax, offset msg                     ; 调用子程序 dispmsg 显示
    call dispmsg

    exit 0
end start

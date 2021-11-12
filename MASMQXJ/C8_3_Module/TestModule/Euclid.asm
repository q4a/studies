; Euclid.asm
;

ifndef __WIN64__
.686
.model flat, c
endif
option casemap:none

; 定义 .asm 的构建规则
;
; 打开 .asm 的属性页
; 1. 首先将 General 中的 Tool 设置为 Custom Build Tool
; 2. 然后在 Custom Build Step > General 中设置 Command Line:
; Debug/Release 配置均生成含调试信息 (/Zi) 的目标文件
; x86 (32bit):
; ml /nologo /c /Zi /Fl"$(IntDir)\$(InputName).lst" /FR"$(IntDir)\$(InputName).sbr" /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"
; x64 (64bit):
; ml64 /nologo /c /Zi /D"__WIN64__" /Fl"$(IntDir)\$(InputName).lst" /FR"$(IntDir)\$(InputName).sbr" /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"
;
; 设置 Outputs:
; $(IntDir)\$(InputName).obj
; $(IntDir)\$(InputName).sbr    [如果不需要用 /FR 生成 Source Browser Information (.sbr), 则不需填入此文件]
;
; 以上 ml 编译命令将在中间目录 $(IntDir) 生成:
; 1. Object File (.obj)
; 2. Assembled Code Listing (.lst)
; 3. Source Browser Information (.sbr)
;
; 关于 Source Browser Information (.sbr) 和 VS 的 Object Browser
; 在 VS IDE 中构建时, 会自动调用 bscmake 将中间目录中的 .sbr 转换为输出目录 $(OutDir) 中的 .bsc
; 将 .bsc 拖放到 VS IDE 中以打开 Object Browser, 可查看 .bsc 中的符号并跳转到相应源码位置
; 当执行完 .sbr 到 .bsc 的自动转换后, .sbr 会变成空文件
; 有时 .sbr 到 .bsc 的自动转换, 会因改变构建命令而突然不起作用了, 即使改回原先的构建命令也不起作用
; 这时关闭 VS 并删除所有生成文件再重启能解决
; .sbr/.bsc 在诊断汇编程序问题时, 没有 .lst 重要, 所以一般不用生成 .sbr

.code

; MASM x86 到 x64 的移植问题:
; 1. MASM x64 汇编器 (ml64) 不支持指示 .386, .model flat, c
; 2. MSVC x64 默认使用 x64 fastcall 调用约定, 而 MSVC x86 默认使用 __cdecl 调用约定
;    MSVC x64 接受但忽略 MSVC x86 的调用约定关键字 __cdecl, __stdcall, __fastcall
;    __cdecl 和 x64 fastcall 在参数传递上的最大区别是:
;    __cdecl 使用栈传递全部参数
;    x64 fastcall 使用 RCX, RDX, R8, R9 传递前 4 个不超过 QWORD 大小的参数, 剩余参数使用栈传递
;
; 两种解决方法:
; 1. 为 x86, x64 分别编写两份 .asm 汇编程序
; 2. 利用条件汇编, 适配 __cdecl 和 x64 fastcall 两种调用约定, 以及 MASM x86/x64 之间的差异
;
; 参考:
; x64 software conventions
; https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions
; .MODEL
; https://docs.microsoft.com/en-us/cpp/assembler/masm/dot-model
; 这里有条件汇编的示例

; 使用欧几里得算法 (Euclid's Algorithm) 求最大公约数:
; Repeatedly subtracting the smaller number from the larger number until zero is reached.
; The number remaining is the greatest common divisor.
ifdef __WIN64__
; MASM x64 中不要声明参数列表, 否则会像 MASM x86 一样自动生成建立/清理栈帧的 prolog/epilog 的代码
; 虽然在 MASM x64 中生成栈帧并没有错误, 但对于只有 [少量参数 + 短小函数体] 的函数而言却是不必要的
Euclid proc
    mov eax, edx
else
; MASM x86
Euclid proc x:sdword, y:sdword
    mov ecx, x
    mov eax, y
endif
@@:
    cmp ecx, eax
    jge NOSWAP
    xchg eax, ecx
NOSWAP:
    sub ecx, eax
    jnz @B
    ; 最大公约数保留在作为返回值的 eax 中
    ret
Euclid endp

end

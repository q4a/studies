; HelloAsm.asm
;

.686
.model flat, c
option casemap:none

includelib msvcrt.lib

_iobuf struct
    _ptr        dword ?
    _cnt        dword ?
    _base       dword ?
    _flag       dword ?
    _file       dword ?
    _charbuf    dword ?
    _bufsiz     dword ?
    _tmpfname   dword ?
_iobuf ends
FILE typedef _iobuf

exit    proto c :dword                          ; void exit(int status)
__p__iob proto c                                ; FILE* __p__iob()
_getch  proto c                                 ; int _getch()
fgets   proto c :ptr sbyte, :dword, :ptr FILE   ; char* fgets(char* str, int n, FILE* stream)
puts    proto c :ptr sbyte                      ; int puts(const char* str)
fputs   proto c :ptr sbyte, :ptr FILE           ; int fputs(const char* str, FILE* stream)
printf  proto c :ptr sbyte, :vararg             ; int printf(const char* fmt, ...)
sscanf  proto c :ptr sbyte, :ptr sbyte, :vararg ; int sscanf(const char* buf, const char* fmt, ...)

__EXIT_PROMPT__ = 1

.const
    GREETING    byte 'Hello World!', 0
    PMT_EXIT    byte 'Press any key to Exit...', 0

.data?
    stdin   dword ?
    stdout  dword ?
    stderr  dword ?

.code
main proc
    call    __p__iob
    mov    stdin, eax           ; #define stdin  (&__iob_func()[0])
    add    eax, sizeof(FILE)
    mov    stdout, eax          ; #define stdout (&__iob_func()[1])
    add    eax, sizeof(FILE)
    mov    stderr, eax          ; #define stderr (&__iob_func()[2])

    invoke puts, offset GREETING

if __EXIT_PROMPT__
    invoke fputs, offset PMT_EXIT, stdout
    invoke _getch
endif
    invoke  exit, 0
main endp
end main

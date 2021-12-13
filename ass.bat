ml /c /coff /Zi "asm\assembler\asm.asm"
link /OPT:NOREF /DEBUG "asm.obj" "asm\Debug\mylib.lib" /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
call asm.exe

call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
cd C:\papka\programms\Git\SVI-2021\compile
ml /c /coff /Zi "..\asm\assembler\asm.asm"
link /OPT:NOREF /DEBUG "asm.obj" "..\asm\Debug\mylib.lib" /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
cls
call asm.exe
echo.
echo.
echo.
pause
exit

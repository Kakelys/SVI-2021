call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
cd C:\papka\programms\Git\SVI-2021\compile
ml /c /coff /Zi "..\SVI-2021\asm\assembler\asm.asm"
link /OPT:NOREF /DEBUG "asm.obj" "..\SVI-2021\asm\Debug\mylib.lib" /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
set Timer=2.5
ping -n %Timer% 127.0.0.1>nul
cls
call asm.exe
echo.
echo.
echo.
pause
exit

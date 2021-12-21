#pragma once


#include "LT.h"
#include "IT.h"
#include "stdafx.h"
#include "LIB.h"
#include "Parm.h"


#define AssPath "C:\papka\programms\Git\SVI-2021\asm\assembler\asm.asm"
#define AssPath1 "C:\\papka\\programms\\Git\\SVI-2021\\asm\\assembler\\asm.asm"

#define START ".586\n"\
	".model flat,stdcall\n"\
	"includelib libucrt.lib\n"\
	"includelib kernel32.lib\n"\

#define EXTERN "\nExitProcess PROTO:DWORD \n"\
"\nlinelength PROTO: DWORD\n"\
"\nprintstr PROTO : DWORD\n"\
"\nprintnumb PROTO : DWORD\n"\
"\nconcats PROTO: DWORD,: DWORD,: DWORD\n"\
"\nfactorial PROTO: DWORD\n"\
"\nprintline PROTO\n"\
".stack 4096\n"


#define CONST ".const\n"\
"ZERO byte 'Ошибка: Деление на нолль', 0\n\n"\
"OVER byte 'Ошибка: Выход за диапазон допустимых значений при присваивании'\n"\
"MIN sdword -32768\n"\
"MAX sdword 32767\n"\

#define DATA ".data\n"\
"\nbuffer1 byte 256 dup(0)\n"\
"buffer2 byte 256 dup(0)\n"\

#define CODE ".code\n"


//В конечном итоге не используется
#define END "push 0\
ncall ExitProcess\
div_by_0:\
push zero\
call printstr\
push -1\
call ExitProcess\
nmain ENDP\
nend main\
"



namespace GEN
{
	void CodeGeneration(LT::LexTable, IT::IdTable, LIB::LibTable lib, wchar_t outfile[]);
}


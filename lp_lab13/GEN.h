#pragma once


#include "LT.h"
#include "IT.h"
#include "stdafx.h"

#define AssPath "C:\apapka\programms\Git\SVI-2021\asm\assembler\asm.asm"
#define AssPath1 "C:\\apapka\\programms\\Git\\SVI-2021\\asm\\assembler\\asm.asm"

#define START ".586\n"\
	".model flat,stdcall\n"\
	"includelib libucrt.lib\n"\
	"includelib kernel32.lib\n"\

#define EXTERN "ExitProcess PROTO:DWORD \n"\
"line_length PROTO: DWORD\n"\
"printstr PROTO : DWORD\n"\
"printnumb PROTO : DWORD\n"\
".stack 4096\n"\


#define CONST ".const\n"
#define DATA ".data\n"

#define CODE ".code\n"

#define END "push 0\ncall ExitProcess\nmain ENDP\nend main"



namespace GEN
{
	void CodeGeneration(LT::LexTable, IT::IdTable);

}


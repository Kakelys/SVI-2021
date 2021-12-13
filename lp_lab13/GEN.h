#pragma once


#include "LT.h"
#include "IT.h"
#include "stdafx.h"
#include "LIB.h"

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
".stack 4096\n"\


#define CONST ".const\n"
#define DATA ".data\n"\
"\nbuffer1 byte 256 dup(0)\n"\
"buffer2 byte 256 dup(0)\n"\

#define CODE ".code\n"

#define END "push 0\ncall ExitProcess\nmain ENDP\nend main"



namespace GEN
{
	void CodeGeneration(LT::LexTable, IT::IdTable, LIB::LibTable lib);
}


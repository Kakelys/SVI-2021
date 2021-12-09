#pragma once
#include "stdafx.h"

#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER "t"
#define LEX_STRING "t"
#define LEX_ID "i"
#define LEX_MAIN "m"
#define LEX_LITERAL "l"
#define LEX_FUNCTION "f"
#define LEX_DECLARE "d"
#define LEX_RETURN "r"
#define LEX_PRINT "p"
#define LEX_SEMICOLON ";"
#define LEX_COMMA ","
#define LEX_LEFTBRACE "{"
#define LEX_RIGHTBRACE "}"
#define LEX_LEFTHESIS "("
#define LEX_RIGHTHESIS ")"
#define LEX_PLUS "v"
#define LEX_MINUS "v"
#define LEX_STAR "v"
#define LEX_DIRSLASH "v"
#define LEX_ARIFM "v"
#define LEX_EQUAL "="
#define LEX_IF "z"
#define LEX_IF_OP "x"
#define LEX_ELSE "c"

//сравнение
#define BIGGER_EQUAL ">="
#define LESS_EQUAL "<="
#define DEQUAL "=="
#define NONEQUAL "!="
#define LESS "<"
#define BIGGER ">"



#define MAIN 'm'
#define ID 'i'
#define FUN '@'
#define LITERAL 'l'
#define FUNCTION 'f'
#define DECLARE 'd'
#define RETURN 'r'
#define PRINT 'p'
#define IF 'z'
#define SEMICILON ';'
#define COMMA ','
#define LEFTBRACE '{'
#define RIGHTBRACE '}'
#define LEFTHESIS '('
#define RIGHTHESIS ')'
#define EQUAL '='
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'








namespace LT
{
	struct Entry
	{
		std::string lexema;
		int linenumber;
		int indexTI;
		int IlLine;

		//для условного оператора
		std::string condition = "";
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);

	void Add(LexTable& lextable, Entry entry);

	Entry GetEntry(LexTable& lextable, int n);

	void Delete(LexTable& lextable);


};




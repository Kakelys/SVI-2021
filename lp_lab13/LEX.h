#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include "Log.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "IT.h"
#include "LT.h"




namespace LEX
{
	void lexTable(wchar_t outfile[], IT::IdTable& idenfs, LT::LexTable& lexems);
	int separat(int Arr[], int sepcount, int linepos);
	void DisplayLT(LT::LexTable lexems);
	void DisplayIT(IT::IdTable idenfs);
};




#define fst_string 7,\
		FST::NODE(1, FST::RELATION('s', 1)),\
		FST::NODE(1, FST::RELATION('t', 2)),\
		FST::NODE(1, FST::RELATION('r', 3)),\
		FST::NODE(1, FST::RELATION('i', 4)),\
		FST::NODE(1, FST::RELATION('n', 5)),\
		FST::NODE(1, FST::RELATION('g', 6)),\
		FST::NODE()

#define fst_integer 4,\
		FST::NODE(1, FST::RELATION('i', 1)),\
		FST::NODE(1, FST::RELATION('n', 2)),\
		FST::NODE(1, FST::RELATION('t', 3)),\
		FST::NODE()

#define fst_function 9,\
		FST::NODE(1, FST::RELATION('f', 1)),\
		FST::NODE(1, FST::RELATION('u', 2)),\
		FST::NODE(1, FST::RELATION('n', 3)),\
		FST::NODE(1, FST::RELATION('c', 4)),\
		FST::NODE(1, FST::RELATION('t', 5)),\
		FST::NODE(1, FST::RELATION('i', 6)),\
		FST::NODE(1, FST::RELATION('o', 7)),\
		FST::NODE(1, FST::RELATION('n', 8)),\
		FST::NODE()

#define fst_declare 8,\
		FST::NODE(1, FST::RELATION('d', 1)),\
		FST::NODE(1, FST::RELATION('e', 2)),\
		FST::NODE(1, FST::RELATION('c', 3)),\
		FST::NODE(1, FST::RELATION('l', 4)),\
		FST::NODE(1, FST::RELATION('a', 5)),\
		FST::NODE(1, FST::RELATION('r', 6)),\
		FST::NODE(1, FST::RELATION('e', 7)),\
		FST::NODE()

#define fst_return 7,\
		FST::NODE(1, FST::RELATION('r', 1)),\
		FST::NODE(1, FST::RELATION('e', 2)),\
		FST::NODE(1, FST::RELATION('t', 3)),\
		FST::NODE(1, FST::RELATION('u', 4)),\
		FST::NODE(1, FST::RELATION('r', 5)),\
		FST::NODE(1, FST::RELATION('n', 6)),\
		FST::NODE()

#define fst_print 6,\
		FST::NODE(1, FST::RELATION('p', 1)),\
		FST::NODE(1, FST::RELATION('r', 2)),\
		FST::NODE(1, FST::RELATION('i', 3)),\
		FST::NODE(1, FST::RELATION('n', 4)),\
		FST::NODE(1, FST::RELATION('t', 5)),\
		FST::NODE()

#define fst_main 5,\
		FST::NODE(1, FST::RELATION('m', 1)),\
		FST::NODE(1, FST::RELATION('a', 2)),\
		FST::NODE(1, FST::RELATION('i', 3)),\
		FST::NODE(1, FST::RELATION('n', 4)),\
		FST::NODE()
//condition
#define fst_if 3,\
		FST::NODE(1, FST::RELATION('i', 1)),\
		FST::NODE(1, FST::RELATION('f', 2)),\
		FST::NODE()

#define fst_if_op 3,\
		FST::NODE(6, FST::RELATION('=', 1),FST::RELATION('!', 1),FST::RELATION('>', 1),FST::RELATION('<', 1),FST::RELATION('>', 2),FST::RELATION('<', 2)),\
		FST::NODE(1, FST::RELATION('=', 2)),\
		FST::NODE()

#define fst_arifm 2,\
		FST::NODE(4, FST::RELATION('+', 1), FST::RELATION('-', 1), FST::RELATION('*', 1), FST::RELATION('/', 1)),\
		FST::NODE()

//abcdefghijklmnopqrstuvwxyz


#define fst_idenf 2,\
			FST::NODE(104,\
			FST::RELATION('a', 0),FST::RELATION('b', 0),FST::RELATION('c', 0),FST::RELATION('d', 0),FST::RELATION('e', 0),FST::RELATION('f', 0),FST::RELATION('g', 0),FST::RELATION('h', 0),FST::RELATION('i', 0),FST::RELATION('j', 0),FST::RELATION('k', 0),FST::RELATION('l', 0),FST::RELATION('m', 0),FST::RELATION('n', 0),FST::RELATION('o', 0),FST::RELATION('p', 0),FST::RELATION('q', 0),FST::RELATION('r', 0),FST::RELATION('s', 0),FST::RELATION('t', 0),FST::RELATION('u', 0),FST::RELATION('v', 0),FST::RELATION('w', 0),FST::RELATION('x', 0),FST::RELATION('y', 0),FST::RELATION('z', 0),	\
			FST::RELATION('A', 0),FST::RELATION('B', 0),FST::RELATION('C', 0),FST::RELATION('D', 0),FST::RELATION('E', 0),FST::RELATION('F', 0),FST::RELATION('G', 0),FST::RELATION('H', 0),FST::RELATION('I', 0),FST::RELATION('J', 0),FST::RELATION('K', 0),FST::RELATION('L', 0),FST::RELATION('M', 0),FST::RELATION('N', 0),FST::RELATION('O', 0),FST::RELATION('P', 0),FST::RELATION('Q', 0),FST::RELATION('R', 0),FST::RELATION('S', 0),FST::RELATION('T', 0),FST::RELATION('U', 0),FST::RELATION('V', 0),FST::RELATION('W', 0),FST::RELATION('X', 0),FST::RELATION('Y', 0),FST::RELATION('Z', 0),\
			FST::RELATION('A', 1),FST::RELATION('B', 1),FST::RELATION('C', 1),FST::RELATION('D', 1),FST::RELATION('E', 1),FST::RELATION('F', 1),FST::RELATION('G', 1),FST::RELATION('H', 1),FST::RELATION('I', 1),FST::RELATION('J', 1),FST::RELATION('K', 1),FST::RELATION('L', 1),FST::RELATION('M', 1),FST::RELATION('N', 1),FST::RELATION('O', 1),FST::RELATION('P', 1),FST::RELATION('Q', 1),FST::RELATION('R', 1),FST::RELATION('S', 1),FST::RELATION('T', 1),FST::RELATION('U', 1),FST::RELATION('V', 1),FST::RELATION('W', 1),FST::RELATION('X', 1),FST::RELATION('Y', 1),FST::RELATION('Z', 1),\
			FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),FST::RELATION('d', 1),FST::RELATION('e', 1),FST::RELATION('f', 1),FST::RELATION('g', 1),FST::RELATION('h', 1),FST::RELATION('i', 1),FST::RELATION('j', 1),FST::RELATION('k', 1),FST::RELATION('l', 1),FST::RELATION('m', 1),FST::RELATION('n', 1),FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1),FST::RELATION('s', 1),FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),FST::RELATION('x', 1),FST::RELATION('y', 1),FST::RELATION('z', 1)), \
			FST::NODE()	

#define fst_integer_literal 3,\
			FST::NODE(19,  FST::RELATION('1', 1),FST::RELATION('2', 1),	FST::RELATION('3', 1),	FST::RELATION('4', 1),	FST::RELATION('5', 1),	FST::RELATION('6', 1),	FST::RELATION('7', 1),	FST::RELATION('8', 1),	FST::RELATION('9', 1),\
						   FST::RELATION('0', 2),FST::RELATION('1', 2),FST::RELATION('2', 2),	FST::RELATION('3', 2),	FST::RELATION('4', 2),	FST::RELATION('5', 2),	FST::RELATION('6', 2),	FST::RELATION('7', 2),	FST::RELATION('8', 2),	FST::RELATION('9', 2)	),					\
			FST::NODE(20, FST::RELATION('0',1), FST::RELATION('1', 1),FST::RELATION('2', 1),	FST::RELATION('3', 1),	FST::RELATION('4', 1),	FST::RELATION('5', 1),	FST::RELATION('6', 1),	FST::RELATION('7', 1),	FST::RELATION('8', 1),	FST::RELATION('9', 1),					\
			FST::RELATION('0',2), FST::RELATION('1', 2),FST::RELATION('2', 2),	FST::RELATION('3', 2),	FST::RELATION('4', 2),	FST::RELATION('5', 2),	FST::RELATION('6', 2),	FST::RELATION('7', 2),	FST::RELATION('8', 2),	FST::RELATION('9', 2)),\
			FST::NODE()


#define fst_string_literal 3,\
	FST::NODE(1, FST::RELATION('"',1)),\
	FST::NODE(64,FST::RELATION(' ', 1), \
				 FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),FST::RELATION('d', 1),FST::RELATION('e', 1),FST::RELATION('f', 1),FST::RELATION('g', 1),FST::RELATION('h', 1),FST::RELATION('i', 1),FST::RELATION('j', 1),FST::RELATION('k', 1),FST::RELATION('l', 1),FST::RELATION('m', 1),FST::RELATION('n', 1),FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1),FST::RELATION('s', 1),FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),FST::RELATION('x', 1),FST::RELATION('y', 1),FST::RELATION('z', 1),\
			     FST::RELATION('A', 1),FST::RELATION('B', 1),FST::RELATION('C', 1),FST::RELATION('D', 1),FST::RELATION('E', 1),FST::RELATION('F', 1),FST::RELATION('G', 1),FST::RELATION('H', 1),FST::RELATION('I', 1),FST::RELATION('J', 1),FST::RELATION('K', 1),FST::RELATION('L', 1),FST::RELATION('M', 1),FST::RELATION('N', 1),FST::RELATION('O', 1),FST::RELATION('P', 1),FST::RELATION('Q', 1),FST::RELATION('R', 1),FST::RELATION('S', 1),FST::RELATION('T', 1),FST::RELATION('U', 1),FST::RELATION('V', 1),FST::RELATION('W', 1),FST::RELATION('X', 1),FST::RELATION('Y', 1),FST::RELATION('Z', 1),\
				 FST::RELATION('0', 1),FST::RELATION('1', 1),FST::RELATION('2', 1),FST::RELATION('3', 1),FST::RELATION('4', 1),FST::RELATION('5', 1),FST::RELATION('6', 1),FST::RELATION('7', 1),FST::RELATION('8', 1),FST::RELATION('9', 1),FST::RELATION('"', 2)),\
	FST::NODE()

#define fst_left_bracket 2,\
	FST::NODE(1, FST::RELATION('(',1)),\
	FST::NODE()

#define fst_right_bracket 2,\
	FST::NODE(1, FST::RELATION(')',1)),\
	FST::NODE()

#define fst_curly_right_bracket 2,\
FST::NODE(1, FST::RELATION('}', 1)), \
FST::NODE()

#define fst_curly_left_bracket 2,\
FST::NODE(1, FST::RELATION('{', 1)), \
FST::NODE()

#define fst_comma 2,\
FST::NODE(1, FST::RELATION(',', 1)), \
FST::NODE()

#define fst_comma_dot 2,\
FST::NODE(1, FST::RELATION(';', 1)), \
FST::NODE()

#define fst_equal 2, \
FST::NODE(1, FST::RELATION('=', 1)),\
FST::NODE()



#pragma once 

#include "stdafx.h"
#include "Error.h"
#include "LT.h"




namespace LT 
{
	LexTable Create(int size) 
	{
		LexTable lex;
		lex.maxsize = size;
		lex.size = 0;
		lex.table = new Entry[size];
		return lex;
	}

	void Add(LexTable& lextable, Entry entry) 
	{
		if (lextable.size == lextable.maxsize) 
		{
			ERROR_THROW_IN(208, NULL, -1);
		}
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry  GetEntry(LexTable& lextable, int n) 
	{
		
	
		return lextable.table[n-1];
	}

	void Delete(LexTable& lextable) 
	{
		delete[] lextable.table;
		//delete& lextable;
	}


}
#include "LIB.h"



namespace LIB 
{

	LibTable Create(int size)
	{
		LibTable lex;
		lex.maxsize = size;
		lex.size = 0;
		lex.table = new Entry[size];
		return lex;
	}

	void Add(LibTable& lib, Entry entry)
	{
		/*if (lextable.size == lextable.maxsize)
		{
			ERROR_THROW_IN(131, NULL, -1);
		}*/
		lib.table[lib.size] = entry;
		
		lib.size++;
	}

	Entry  GetEntry(LibTable& lib, int n)
	{
		/*if (n<0 || n>lextable.size)
		{
			throw ERROR_THROW(130);
		}*/

		return lib.table[n - 1];
	}

	void Delete(LibTable& lib)
	{
		delete[] lib.table;
		
	}

	void AddSomeFunc(LibTable& libs) 
	{
		LIB::Entry lib;
		lib.name = "linelength";
		lib.ParmCounter = 1;
		lib.datatype = 1;
		lib.elem = new LIB::Elem[lib.ParmCounter];
		lib.elem[0].datatype = 2;
		LIB::Add(libs, lib);
		delete lib.elem;
	
		lib.name = "factorial";
		lib.ParmCounter = 1;
		lib.datatype = 1;
		lib.elem = new LIB::Elem[lib.ParmCounter];
		lib.elem[0].datatype = 1;
		LIB::Add(libs, lib);
	
	}

}
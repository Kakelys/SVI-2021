#pragma once
#include "stdafx.h"

namespace LIB 
{
	struct Elem
	{
		int datatype = 0;
	};


	struct Entry
	{
		std::string name;
		int datatype;
		int ParmCounter;
		int size;
		//Добавление параметров
		
		
		Elem* elem;
		
	};


	struct LibTable
	{
		int maxsize;
		int size;
		Entry* table;
	};


	LibTable Create(int size);

	void Add(LibTable& lib, Entry entry);

	Entry GetEntry(LibTable& lib, int n);

	void Delete(LibTable& lib);

	void AddSomeFunc(LibTable& lib);
}
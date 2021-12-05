#pragma once
#include "stdafx.h"
#include "Error.h"
#include "IT.h"

#pragma warning(disable : 6262)


namespace IT 
{

	IdTable Create(int size) 
	{
		IdTable idenfs;
		idenfs.maxsize = size;
		idenfs.size = 0;
		idenfs.table = new Entry[size];

			return idenfs;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n) 
	{
		if (n<0 || n>idtable.size)
		{
			throw ERROR_THROW(130);
		}

		return idtable.table[n - 1];
	}

	int IsId(IdTable& idtable, std::string name, int scope, int subscope)
	{
		Entry Idenf;
		bool find = false;
		int numbline = 1;
		for (; numbline < idtable.size+1; numbline++) 
		{
		Idenf=GetEntry(idtable, numbline);
		if (Idenf.name == name && (Idenf.scope == scope && Idenf.subscope == subscope-1 || Idenf.scope == scope && Idenf.subscope == subscope))
		{
			
			find = true;
			break;
		}
		}
		if (find == true) 
		{
			if (Idenf.name == "lit") 
			{
				return IT_NULLIDX;
			}
			else
			{
				return Idenf.indexfirstLE;
			}
		}
		else 
		{
			return IT_NULLIDX;
		}
		
	}

	int GetNumberOfIdenf(IdTable& idtable, std::string name, int scope, int subscope) 
	{
		Entry Idenf;
		bool find = false;
		int numbline = 1;
		for (; numbline < idtable.size + 1; numbline++)
		{
			Idenf = GetEntry(idtable, numbline);
			if (Idenf.name == name && Idenf.scope == scope && Idenf.subscope == subscope)
			{
				find = true;
				break;
			}
		}
		if (find == true)
		{
			return numbline;
		}
		else
		{
			return IT_NULLIDX;
		}
	}
	std::string GetLastFunc(IdTable& idenfs, LT::LexTable lexems, int n) 
	{
		for (int i = n; i >= 1; i--) 
		{
			if (lexems.table[i - 1].indexTI < 0) { continue; }
			if (idenfs.table[lexems.table[i - 1].indexTI].type == 2) 
			{
				if (idenfs.table[lexems.table[n - 1].indexTI].name.find(idenfs.table[lexems.table[i - 1].indexTI].name) < 999) 
				{
					return idenfs.table[lexems.table[i - 1].indexTI].name;
				}
			}
		}
	
	
	}

	bool AlredyExist(IT::IdTable idenfs, int n, std::string name)
	{
		for (int i = 0; i < n; i++)
		{
			if (idenfs.table[i].name == name) { return true; }
		}
		return false;
	}

	bool IsFun(IT::IdTable idenfs, int n, std::string name) 
	{
		for (int i = 0; i < idenfs.size; i++)
		{
			if (idenfs.table[i].name == name && idenfs.table[i].type == 2) { return true; }
		}
		return false;
	}
	int TakeDataType(IT::IdTable idenfs, std::string name)
	{
		for (int i = 0; i < idenfs.size; i++)
		{
			if (idenfs.table[i].name == name) { return idenfs.table[i].datatype; }
		}
		return 1;
	}


	void Delete(IdTable& idtable) 
	{
		delete[] idtable.table;
		//delete& idtable;
	}
}
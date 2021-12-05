#pragma once
#include "stdafx.h"
#include "LT.h"
#define ID_MAXSIZE 5
#define IT_MAXSIZE 4096
#define IT_INT_DEFAULT 0x00000000
#define IT_STR_DEFAULT 0x00
#define IT_NULLIDX 0xffffffff
#define IT_STR_MAXSIZE 255



namespace IT
{
	// enum IDDATATYPE { INT = 1, STR = 2 };
	//enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };


	struct Entry
	{
		int indexfirstLE;
		std::string name;
		int scope;
		int subscope;
		int datatype;
		int type;

		/*IDDATATYPE datatype;
		IDTYPE type;*/
		int ParmCount = 0; //кол-во параметров у функции
		union
		{
			int vint;
			

			struct
			{
				char len;
				char str[IT_STR_MAXSIZE-1];
			}vstr[IT_STR_MAXSIZE-1];

		}value;


	};

	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	IdTable Create(int size);

	void Add(IdTable& idtable, Entry entry);

	Entry GetEntry(IdTable& idtable, int n);

	int IsId(IdTable& idtable, std::string name, int scope, int subscope);

	int GetNumberOfIdenf(IdTable& idtable, std::string name, int scope, int subscope);

	std::string GetLastFunc(IdTable& idtable, LT::LexTable lexems, int n);

	void Delete(IdTable& idtable);

	bool AlredyExist(IT::IdTable idenfs, int n, std::string name);

	//Если существует, взять тип данных
	int TakeDataType(IT::IdTable idenfs, std::string name);
	//Является ли функцией в таблице 
	bool IsFun(IT::IdTable idenfs, int n, std::string name);

};

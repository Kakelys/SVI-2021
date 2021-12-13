#include "SEM.h"



namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable lib) 
	{
		//Проверка наличие мэйна и один ли он
		MainCheck(idenfs,lexems);
		//Проверка на повторное объявление идентификаторов
		DoubleIdenfsCheck(idenfs, lexems);
		//Проверка на повторяющиеся функции
		DoubleFuncCheck(idenfs, lexems);
		//Проверка на то, что каждый используемый идентификатор должен быть проинициализирован
		CheckAvailableIdenfs(idenfs, lexems);
		//Проверка соответствия типов левой и правой части
		CheckTypeInEqual(idenfs, lexems);
		//Проверка типа ретурна с типом функции
		CheckReturnType(idenfs, lexems);
		//Проверить, чтобы библиотечные функции не переопределялись и в прототипы было нужное кол-во параметров
		LibFuncCheck(idenfs, lexems, lib);
		//Проверка на пустые строки(ассемблер их не любит)
		NullLiteralCheck(idenfs, lexems);
		//Числовое значение попадает в диапазон допустимых значений
		CheckValueOfNumb(idenfs, lexems);
		//Проверка на кол-во параметров в функции и их кол-во
		CallFuncCheck(idenfs,lexems);
		//Проверка конкатенации строк(Должен быть только +)
		CheckConcat(idenfs, lexems);
	}
	
	void MainCheck(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		bool main = false;
		for (int i = 0; i < lexems.size; i++)
		{
			if (lexems.table[i].lexema == LEX_MAIN) 
			{
				if(main == true){ ERROR_THROW_IN(127, lexems.table[i].linenumber, 0); }
				main = true;
			}
		}
		if (main == false) 
		{
			ERROR_THROW_IN(128, -1, -1);
		}
	}


	void CheckTypeInEqual(IT::IdTable idenfs, LT::LexTable lexems)
	{
		int lefttype = 0;
		bool find = false;
		for (int i = 0; i < lexems.size; i++) 
		{
			//нахождение выражения
			if (lexems.table[i].lexema == LEX_EQUAL && lexems.table[i + 1].lexema != LEX_EQUAL) 
			{
				lefttype = idenfs.table[lexems.table[i - 1].indexTI].datatype;
				find = true;
			}
			//Если выражение было найдено
			if (find == true) 
			{
				//Если идентификатор
				if (lexems.table[i].lexema == LEX_ID) 
				{
					//Проверка соответствия типа левой части и найденного идентификатора
					if (idenfs.table[lexems.table[i].indexTI].datatype != lefttype) 
					{
						ERROR_THROW_IN(123, lexems.table[i].linenumber, 0);
					}
					


					//Если идентификатор - функция, то пропустить до скобки
					if (idenfs.table[lexems.table[i].indexTI].type == 2) 
					{
						while (lexems.table[i].lexema != LEX_RIGHTHESIS) 
						{
							i++;
						}
					}
					
					
				}
				//Если ; - конец выражения
				if (lexems.table[i].lexema == LEX_SEMICOLON) 
				{
					find = false;
				}
			}
			
		}
	
		
	}

	void CheckReturnType(IT::IdTable idenfs, LT::LexTable lexems)
	{
		int FuncType;
		for (int i = 0; i < lexems.size; i++) 
		{
			

			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_FUNCTION || lexems.table[i].lexema == LEX_MAIN)
			{
				//Проверить, не является ли библиотечной функцией 
				bool checked = true;
				for (int j = i; ;j++) 
				{
					if (lexems.table[j].lexema == LEX_RIGHTHESIS) 
					{
					if(lexems.table[j+1].lexema == LEX_SEMICOLON)
					{
						checked = false;
					}
					break;
					}
				
				}
				if (!checked) { break; }



				if (lexems.table[i].lexema == LEX_MAIN) { FuncType = 1; }
				else {
					FuncType = idenfs.table[lexems.table[i].indexTI].datatype;
				}
				while (lexems.table[i].lexema != "r") { i++; }
				//Проверка типа возвращаемого значения с типов функции
				if (FuncType != idenfs.table[lexems.table[i + 1].indexTI].datatype) 
				{
					ERROR_THROW_IN(121, lexems.table[i].linenumber, 0);
				}

			}

		}
	}

	void DoubleFuncCheck(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		for (int i = 0; i < lexems.size; i++)
		{

			int FindPos = -1;
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_FUNCTION)
			{
				FindPos = i; std::string FuncName = idenfs.table[lexems.table[i].indexTI].name;
				while (i < lexems.size) 
				{
					i++;
					if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_FUNCTION) 
					{
						if (idenfs.table[lexems.table[i].indexTI].name == FuncName) { ERROR_THROW_IN(129, lexems.table[i].linenumber, 0); }
					}
					
				}
				i = FindPos;
			}

		}
	
	}


	void CheckAvailableIdenfs(IT::IdTable idenfs, LT::LexTable lexems)
	{
		std::string name;
		for (int i = 0; i < lexems.size; i++) 
		{
		//Нахождение идентификатора, который используется, а не объявляется
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema != LEX_FUNCTION && lexems.table[i - 1].lexema != LEX_INTEGER  && lexems.table[i + 1].lexema != LEX_RIGHTHESIS && idenfs.table[lexems.table[i].indexTI].datatype != 4)
			{
				bool find = false;
				name = idenfs.table[lexems.table[i].indexTI].name;
			
				for (int j = i; j > 0; j--) 
				{
					//Нахождение определений идентификаторов и сравнение по имени
					if (lexems.table[j].lexema == LEX_ID && lexems.table[j-1].lexema == LEX_INTEGER || lexems.table[j].lexema == LEX_ID && lexems.table[j - 1].lexema == LEX_FUNCTION)
					{
						if (idenfs.table[lexems.table[j].indexTI].name == name) 
						{
							find = true;
						}
					}
				
				}
				if (find == false) 
				{
				
					ERROR_THROW_IN(125, lexems.table[i].linenumber, 0);
				}
			}
		}
	}

	void DoubleIdenfsCheck(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		for (int i = 0; i < lexems.size; i++) 
		{
			//Находим конструкцию типа ti
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_STRING) 
			{
				//Записываем идентификатор в отдельную переменную
				std::string name = idenfs.table[lexems.table[i].indexTI].name;
				for (int j = i - 1; j > 0; j--) 
				{
					//Нахождение конструкций ti или fi до первой и сравнение по имени
					if (lexems.table[j].lexema == LEX_ID && lexems.table[j - 1].lexema == LEX_STRING || lexems.table[j].lexema == LEX_ID && lexems.table[j - 1].lexema == LEX_FUNCTION)
					{
						if (idenfs.table[lexems.table[j].indexTI].name == name) 
						{
							ERROR_THROW_IN(132, lexems.table[i].linenumber, 0);
						}
					}
				}
			}
		}
	}
	void LibFuncCheck(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable lib)
	{
		for (int i = 0; i < lexems.size; i++) 
		{
			//Найти функцию
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_FUNCTION) 
			{
				int ParmCount = -1, WhatLib =-1;
				//Проверить, является ли библиотечной, если да - взять кол-во параметров и номер функции в библиотеке
				for (int j = 0; j < lib.size; j++) 
				{
					if (idenfs.table[lexems.table[i].indexTI].name == lib.table[j].name) { ParmCount = lib.table[j].ParmCounter; WhatLib = j; }
				}
				if (ParmCount == -1) { continue; }
				//Проверить, чтобы был прототип, а не переопределение
				for (int j = i;; j++) 
				{
					//Сама проверка
					if (lexems.table[j].lexema == LEX_RIGHTHESIS) 
					{
						if (lexems.table[j + 1].lexema != LEX_SEMICOLON) {
							ERROR_THROW_IN(124, lexems.table[i].linenumber, 0);
						}
						break;
					}
				}
				//Проверка на кол-во параметров и их типы
				int FuncParmCounter = 0;
				for (int j = i + 1; lexems.table[j].lexema != LEX_RIGHTHESIS; j++) 
				{
					if (lexems.table[j].lexema == LEX_ID) 
					{
						if (lib.table[WhatLib].elem[FuncParmCounter].datatype != idenfs.table[lexems.table[j].indexTI].datatype) 
						{
							ERROR_THROW_IN(124, lexems.table[i].linenumber, 0);
						}
						FuncParmCounter++;
					}
				}
				//Если не нашлось переменных
				if (ParmCount != FuncParmCounter) { ERROR_THROW_IN(124, lexems.table[i].linenumber, 0); }
			}
		}
	}
	void CheckConcat(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		for (int i = 0; i < lexems.size; i++) 
		{
			// Поиск присваивания
			if (lexema(i) == LEX_ID && lexema(i + 1) == LEX_EQUAL) 
			{
				//Что это строка
				if (idenf(i).datatype == 2) 
				{
					//Доступна только конкатенация, т.е. +
					for (int j = i + 2; lexema(j) != LEX_SEMICOLON; j++) 
					{
						if (lexema(j) == LEX_STAR || lexema(j) == LEX_DIRSLASH || lexema(j) == LEX_MINUS) 
						{
							ERROR_THROW_IN(137, lexems.table[i].linenumber, 0);
						}
					}
				
				}
			
			}
		
		}


	}



	void NullLiteralCheck(IT::IdTable idenfs, LT::LexTable lexems)
	{
		for (int i =0;i < lexems.size; i++) 
		{
			if (lexems.table[i].lexema == LEX_LITERAL) 
			{
				if (idenfs.table[lexems.table[i].indexTI].datatype == 2) 
				{
					std::string value = idenfs.table[lexems.table[i].indexTI].value.vstr->str;
					if (value == "") { ERROR_THROW_IN(133, lexems.table[i].linenumber, 0);}
				}
			}
		}
	}
	void CheckValueOfNumb(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		for (int i = 0; i < lexems.size; i++)
		{
			if (lexems.table[i].lexema == LEX_LITERAL)
			{
				if (idenfs.table[lexems.table[i].indexTI].datatype == 1)
				{
					int value = idenfs.table[lexems.table[i].indexTI].value.vint;
					if (value > 32767 || value < -32768) { ERROR_THROW_IN(134, lexems.table[i].linenumber, 0); }
				}
			}
		}


	}
	void CallFuncCheck(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		LIB::LibTable lib = LIB::Create(MAX_LIB);
		//Создание 
		AddAllFunctions(idenfs, lexems, lib);
		for (int i = 0; i < lexems.size; i++) 
		{
			//Поиск вызов функций
			if (lexema(i) == LEX_ID && lexema(i + 1) == LEX_LEFTHESIS && lexema(i-1)!=LEX_FUNCTION) 
			{
				//Номер функции в библиотеке и кол-во параметров
				int WhatFunc = -1, ParmCounter = -1;
				for (int j = 0; j < lib.size; j++)
				{
					if (idenf(i).name == lib.table[j].name) 
					{
						WhatFunc = j;
						ParmCounter = lib.table[j].ParmCounter;
						break;
					}
				}
				//Проверка на кол-во параметров и их тип в вызываемой функции
				int CallFuncParamsCount = 0;
				for (int j = i+1; lexema(j)!=LEX_RIGHTHESIS; j++) 
				{
					if (lexema(j) == LEX_ID || lexema(j) == LEX_LITERAL) 
					{
						if (idenf(j).datatype != lib.table[WhatFunc].elem[CallFuncParamsCount].datatype) 
						{
							ERROR_THROW_IN(135, lexems.table[i].linenumber, 0);
							CallFuncParamsCount++;
						}
						//Соответствие кол-ва параметров в вызываемой функции и её объявлению
						if (CallFuncParamsCount != lib.table[WhatFunc].ParmCounter) {}
					}
				
				}
			}
		
		}

	}
	void AddAllFunctions(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable& libs)
	{
		for (int i = 0; i < lexems.size; i++) 
		{
			//Поиск определение функций
		if(lexema(i) == LEX_ID && lexema(i-1) == LEX_FUNCTION)
		{
			//Создание функции для добавления в библиотеку
			LIB::Entry lib;
			lib.ParmCounter = idenf(i).ParmCount;
			lib.name = idenf(i).name;
			lib.datatype = idenf(i).datatype;
			lib.elem = new LIB::Elem[lib.ParmCounter];
			//увеличение i для того, чтобы не посчитать функцию как параметр
			i++;
			for (int j = 0; lexema(i) != LEX_RIGHTHESIS; i++) 
			{
				//Добавление параметров к функции
				if (lexema(i) == LEX_ID) 
				{
					lib.elem[j].datatype = idenf(i).datatype;
					j++;
				}
			
			}
			LIB::Add(libs, lib);
		}
		
		}
	
	}

}
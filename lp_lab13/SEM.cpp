#include "SEM.h"




namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		OneMainCheck(idenfs,lexems);
		CheckTypeInEqual(idenfs, lexems);


	}
	
	void OneMainCheck(IT::IdTable idenfs, LT::LexTable lexems) 
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
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_FUNCTION) 
			{
				FuncType = idenfs.table[lexems.table[i].indexTI].datatype;
				while (lexems.table[i].lexema != "r") { i++; }
				//Проверка типа возвращаемого значения с типов функции
				if (FuncType != idenfs.table[lexems.table[i + 1].indexTI].datatype) 
				{
					ERROR_THROW_IN(123, lexems.table[i].linenumber, 0);
				}

			}

		}
	}
}
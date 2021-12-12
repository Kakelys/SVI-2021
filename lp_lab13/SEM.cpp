#include "SEM.h"




namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems) 
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
		//Проверить, чтобы библиотечные функции не переопределялись
		LibFuncCheck(idenfs, lexems);
		//Проверка на пустые строки(ассемблер их не любит)
		NullLiteralCheck(idenfs, lexems);
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
	void LibFuncCheck(IT::IdTable idenfs, LT::LexTable lexems) 
	{
	
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
}
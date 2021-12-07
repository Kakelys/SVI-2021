#include "SEM.h"




namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		MainCheck(idenfs,lexems);
		DoubleFuncCheck(idenfs, lexems);
		CheckTypeInEqual(idenfs, lexems);
		CheckReturnType(idenfs, lexems);
		
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
			//���������� ���������
			if (lexems.table[i].lexema == LEX_EQUAL && lexems.table[i + 1].lexema != LEX_EQUAL) 
			{
				lefttype = idenfs.table[lexems.table[i - 1].indexTI].datatype;
				find = true;
			}
			//���� ��������� ���� �������
			if (find == true) 
			{
				//���� �������������
				if (lexems.table[i].lexema == LEX_ID) 
				{
					//�������� ������������ ���� ����� ����� � ���������� ��������������
					if (idenfs.table[lexems.table[i].indexTI].datatype != lefttype) 
					{
						ERROR_THROW_IN(123, lexems.table[i].linenumber, 0);
					}
					


					//���� ������������� - �������, �� ���������� �� ������
					if (idenfs.table[lexems.table[i].indexTI].type == 2) 
					{
						while (lexems.table[i].lexema != LEX_RIGHTHESIS) 
						{
							i++;
						}
					}
					
					
				}
				//���� ; - ����� ���������
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
				if (lexems.table[i].lexema == LEX_MAIN) { FuncType = 1; }
				else {
					FuncType = idenfs.table[lexems.table[i].indexTI].datatype;
				}
				while (lexems.table[i].lexema != "r") { i++; }
				//�������� ���� ������������� �������� � ����� �������
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
}
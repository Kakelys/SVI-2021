#include "SEM.h"



namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable lib) 
	{
		//�������� ������� ����� � ���� �� ��
		MainCheck(idenfs,lexems);
		//�������� �� ��������� ���������� ���������������
		DoubleIdenfsCheck(idenfs, lexems);
		//�������� �� ������������� �������
		DoubleFuncCheck(idenfs, lexems);
		//�������� �� ��, ��� ������ ������������ ������������� ������ ���� ������������������
		CheckAvailableIdenfs(idenfs, lexems);
		//�������� ������������ ����� ����� � ������ �����
		CheckTypeInEqual(idenfs, lexems);
		//�������� ���� ������� � ����� �������
		CheckReturnType(idenfs, lexems);
		//���������, ����� ������������ ������� �� ���������������� � � ��������� ���� ������ ���-�� ����������
		LibFuncCheck(idenfs, lexems, lib);
		//�������� �� ������ ������(��������� �� �� �����)
		NullLiteralCheck(idenfs, lexems);
		//�������� �������� �������� � �������� ���������� ��������
		CheckValueOfNumb(idenfs, lexems);
		//�������� �� ���-�� ���������� � ������� � �� ���-��
		CallFuncCheck(idenfs,lexems);
		//�������� ������������ �����(������ ���� ������ +)
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
				//���������, �� �������� �� ������������ �������� 
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


	void CheckAvailableIdenfs(IT::IdTable idenfs, LT::LexTable lexems)
	{
		std::string name;
		for (int i = 0; i < lexems.size; i++) 
		{
		//���������� ��������������, ������� ������������, � �� �����������
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema != LEX_FUNCTION && lexems.table[i - 1].lexema != LEX_INTEGER  && lexems.table[i + 1].lexema != LEX_RIGHTHESIS && idenfs.table[lexems.table[i].indexTI].datatype != 4)
			{
				bool find = false;
				name = idenfs.table[lexems.table[i].indexTI].name;
			
				for (int j = i; j > 0; j--) 
				{
					//���������� ����������� ��������������� � ��������� �� �����
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
			//������� ����������� ���� ti
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_STRING) 
			{
				//���������� ������������� � ��������� ����������
				std::string name = idenfs.table[lexems.table[i].indexTI].name;
				for (int j = i - 1; j > 0; j--) 
				{
					//���������� ����������� ti ��� fi �� ������ � ��������� �� �����
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
			//����� �������
			if (lexems.table[i].lexema == LEX_ID && lexems.table[i - 1].lexema == LEX_FUNCTION) 
			{
				int ParmCount = -1, WhatLib =-1;
				//���������, �������� �� ������������, ���� �� - ����� ���-�� ���������� � ����� ������� � ����������
				for (int j = 0; j < lib.size; j++) 
				{
					if (idenfs.table[lexems.table[i].indexTI].name == lib.table[j].name) { ParmCount = lib.table[j].ParmCounter; WhatLib = j; }
				}
				if (ParmCount == -1) { continue; }
				//���������, ����� ��� ��������, � �� ���������������
				for (int j = i;; j++) 
				{
					//���� ��������
					if (lexems.table[j].lexema == LEX_RIGHTHESIS) 
					{
						if (lexems.table[j + 1].lexema != LEX_SEMICOLON) {
							ERROR_THROW_IN(124, lexems.table[i].linenumber, 0);
						}
						break;
					}
				}
				//�������� �� ���-�� ���������� � �� ����
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
				//���� �� ������� ����������
				if (ParmCount != FuncParmCounter) { ERROR_THROW_IN(124, lexems.table[i].linenumber, 0); }
			}
		}
	}
	void CheckConcat(IT::IdTable idenfs, LT::LexTable lexems) 
	{
		for (int i = 0; i < lexems.size; i++) 
		{
			// ����� ������������
			if (lexema(i) == LEX_ID && lexema(i + 1) == LEX_EQUAL) 
			{
				//��� ��� ������
				if (idenf(i).datatype == 2) 
				{
					//�������� ������ ������������, �.�. +
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
		//�������� 
		AddAllFunctions(idenfs, lexems, lib);
		for (int i = 0; i < lexems.size; i++) 
		{
			//����� ����� �������
			if (lexema(i) == LEX_ID && lexema(i + 1) == LEX_LEFTHESIS && lexema(i-1)!=LEX_FUNCTION) 
			{
				//����� ������� � ���������� � ���-�� ����������
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
				//�������� �� ���-�� ���������� � �� ��� � ���������� �������
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
						//������������ ���-�� ���������� � ���������� ������� � � ����������
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
			//����� ����������� �������
		if(lexema(i) == LEX_ID && lexema(i-1) == LEX_FUNCTION)
		{
			//�������� ������� ��� ���������� � ����������
			LIB::Entry lib;
			lib.ParmCounter = idenf(i).ParmCount;
			lib.name = idenf(i).name;
			lib.datatype = idenf(i).datatype;
			lib.elem = new LIB::Elem[lib.ParmCounter];
			//���������� i ��� ����, ����� �� ��������� ������� ��� ��������
			i++;
			for (int j = 0; lexema(i) != LEX_RIGHTHESIS; i++) 
			{
				//���������� ���������� � �������
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
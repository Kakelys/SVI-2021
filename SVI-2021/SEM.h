#pragma once
#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "LEX.h"
#include "Error.h"
#include "LIB.h"



namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable lib);
	//�������� ������� ����� � �� ����
	void MainCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� ������������ ����� ����� � ������ �����
	void CheckTypeInEqual(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� ���� ������� � ����� �������
	void CheckReturnType(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� �� ������������� �������
	void DoubleFuncCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� �� ��, ��� ������ ������������ ������������� ������ ���� ������������������
	void CheckAvailableIdenfs(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� �� ��������� ���������� ���������������
	void DoubleIdenfsCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//���������, ����� ������������ ������� �� ���������������� � � ��������� ���� ������ ���-�� ����������
	void LibFuncCheck(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable lib);
	//�������� �� ���-�� ���������� � ������� � �� ���-��
	void CallFuncCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� �� ������ ������ � ���������
	void NullLiteralCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� �������� �������� � �������� ���������� ��������
	void CheckValueOfNumb(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� ������������ �����(������ ���� ������ +)
	void CheckConcat(IT::IdTable idenfs, LT::LexTable lexems);
	//� ��������� ������ int
	void CheckTypesIF(IT::IdTable idenfs, LT::LexTable lexems);




	//���������� ���� ��������� ������� � ����������
	void AddAllFunctions(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable& libs);
}


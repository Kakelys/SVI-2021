#pragma once
#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "LEX.h"
#include "Error.h"


namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� �� ���� ����
	void OneMainCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� ������������ ����� ����� � ������ �����
	void CheckTypeInEqual(IT::IdTable idenfs, LT::LexTable lexems);
	//�������� ���� ������� � ����� �������
	void CheckReturnType(IT::IdTable idenfs, LT::LexTable lexems);
}

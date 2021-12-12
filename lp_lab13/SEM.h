#pragma once
#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "LEX.h"
#include "Error.h"


namespace SEM 
{
	void CheckSemantics(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка наличие мэйна и он один
	void MainCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка соответствия типов левой и правой части
	void CheckTypeInEqual(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка типа ретурна с типом функции
	void CheckReturnType(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка на повторяющиеся функции
	void DoubleFuncCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка на то, что каждый используемый идентификатор должен быть проинициализирован
	void CheckAvailableIdenfs(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка на повторное объявление идентификаторов
	void DoubleIdenfsCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверить, чтобы библиотечные функции не переопределялись
	void LibFuncCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка на кол-во параметров в функции
	//void CallFuncCheck(IT::IdTable idenfs, LT::LexTable lexem);
	//Проверка на пустые строки в литералах
	void NullLiteralCheck(IT::IdTable idenfs, LT::LexTable lexems);
}


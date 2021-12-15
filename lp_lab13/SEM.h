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
	//Проверить, чтобы библиотечные функции не переопределялись и в прототипе было нужное кол-во параметров
	void LibFuncCheck(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable lib);
	//Проверка на кол-во параметров в функции и их кол-во
	void CallFuncCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка на пустые строки в литералах
	void NullLiteralCheck(IT::IdTable idenfs, LT::LexTable lexems);
	//Числовое значение попадает в диапазон допустимых значений
	void CheckValueOfNumb(IT::IdTable idenfs, LT::LexTable lexems);
	//Проверка конкатенации строк(Должен быть только +)
	void CheckConcat(IT::IdTable idenfs, LT::LexTable lexems);
	//В сравнении только int
	void CheckTypesIF(IT::IdTable idenfs, LT::LexTable lexems);




	//Добавление всех найденных функций в библиотеку
	void AddAllFunctions(IT::IdTable idenfs, LT::LexTable lexems, LIB::LibTable& libs);
}


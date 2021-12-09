#include "stdafx.h"
#include <fstream>
#include <string>
#include "In.h"
#include "Error.h"
#include "FST.h"
namespace Error
{
	//
	//
	//
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка при открытии файла с промежуточным кодом (il.txt)"),
		ERROR_ENTRY(114, "Больше 5 символов в идентификаторе в строке: "),
		ERROR_ENTRY(115, "Big letter in idenf, line: "),
		ERROR_ENTRY(116, "Idenf matches with keyword, line: "),
		ERROR_ENTRY(117, "В параметрах функции ошибка, строка: "),
		ERROR_ENTRY(118, "Ошибка в написании идентификатора перед функцией, строка: "),
		ERROR_ENTRY(119, "В идентификаторе обнаружен не символ, строка: "),
		ERROR_ENTRY(120, "Неверное ключевое слово или идентификатор, строка: "),
		ERROR_ENTRY(121, "The return type does not match the function type, line: "),
		ERROR_ENTRY(122, "Не найдена ни одна встроенная функция, совпадающая с идетификатором, строка: "),
		ERROR_ENTRY(123, "data types of right and left part non equal, line: "),
		ERROR_ENTRY(124, "Text after ; , строка: "),
		ERROR_ENTRY(125, "Idenfs doesn't exist, line "),
		ERROR_ENTRY(126, "Failed to create Polish Notation , line: "),
		ERROR_ENTRY(127, "More than one main"),
		ERROR_ENTRY(128, "No main"),
		ERROR_ENTRY(129, "This Function Already Exist, line "),
		ERROR_ENTRY(130, "Lex Table"),
		ERROR_ENTRY(131, "exceeded the limit of operations"),
		ERROR_ENTRY_NODEF(132), ERROR_ENTRY_NODEF(133), ERROR_ENTRY_NODEF(134), ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы, line "),
		ERROR_ENTRY(601, "Ошибочный оператор, line "),
		ERROR_ENTRY(602, "Ошибка в выражении, line "),
		ERROR_ENTRY(603, "Ошибка в выражении, line "),
		ERROR_ENTRY(604, "Ошибка в параметрах функции, line "),
		ERROR_ENTRY(605, "Ошибка в параметрах вызываемой функции, line "),
		ERROR_ENTRY(606, "Wrong parameters in conditional function, line"),
		ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
	};
	ERROR geterror(int id)
	{
		if ((id > 0) && (id < ERROR_MAX_ENTRY))
		{
			ERROR err = { errors[id].id };
			for (int i = 0; i < ERROR_MAXSIZE_MESSAGE; i++)
				err.message[i] = errors[id-2].message[i];
			return err;
		}
		else
		{
			ERROR err = { errors[0].id };
			for (int i = 0; i < ERROR_MAXSIZE_MESSAGE; i++)
				err.message[i] = errors[0].message[i];
			return err;
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if ((id > 0) && (id < ERROR_MAX_ENTRY))
		{
			ERROR err = { errors[id].id};
			for (int i = 0; i < ERROR_MAXSIZE_MESSAGE; i++)
				err.message[i] = errors[id].message[i];
			err.index.line = line;
			err.index.col = col;
			throw err;
			return err;
		}
		else
		{
			ERROR err = { errors[0].id };
			for (int i = 0; i < ERROR_MAXSIZE_MESSAGE; i++)
				err.message[i] = errors[0].message[i];
			err.index.line = line;
			err.index.col = col;
			throw err;
			return err;
		}
	}
}
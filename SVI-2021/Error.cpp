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
		ERROR_ENTRY_NODEF(110), ERROR_ENTRY_NODEF(111), 
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка при открытии файла с промежуточным кодом (il.txt)"),
		ERROR_ENTRY(114, "Ошибка при открытии файла для генерации кода (-out)"),
		ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY(117, "В параметрах функции ошибка, строка "),
		ERROR_ENTRY(118, "Ошибка в написании идентификатора перед функцией, строка: "),
		ERROR_ENTRY(119, "В идентификаторе обнаружен не символ, строка: "),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		//Лексический
		ERROR_ENTRY(200, "Ошибка при открытии файла с исходным кодом(-in)"), //110
		ERROR_ENTRY(201, "Недопустимый символ в файле с исходным кодом (-in), строка "), //111 
		ERROR_ENTRY_NODEF(202),ERROR_ENTRY_NODEF(203),
		ERROR_ENTRY(204, "Превышен лимит в размере строки литерала, строка  "), //114
		ERROR_ENTRY(205, "Неверный символ в идентификаторе, строка "), //115
		ERROR_ENTRY(206, "Неверное ключевое слово или идентификатор, строка: "), //120
		ERROR_ENTRY(207, "Идентификатор совпадает с ключевым словом, строка "), //116
		ERROR_ENTRY(208, "Выход за пределы таблицы лексем"), // 131
		ERROR_ENTRY(209, "Выход за пределы таблицы идентификаторов"), 
		

		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220),ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		//Семантика
		ERROR_ENTRY(300, "Тип return не соответствует типу функции, строка "),//121
		ERROR_ENTRY(301, "Типы правой и левой части отличаются, строка "), //123
		ERROR_ENTRY(302, "Попытка переопределения библиотечной функции, строка "), //124
		ERROR_ENTRY(303, "Идентификатор не существует, строка "), //125
		ERROR_ENTRY(304, "Возникла ошибка при создании польской записи: "), //126
		ERROR_ENTRY(305, "Несколько точек входа main"), //127
		ERROR_ENTRY(306, "Нет начала программы(main)"), //128
		ERROR_ENTRY(307, "Попытка переопределения функции, строка "), //129
		ERROR_ENTRY(308, "Попытка переопределения переменной, строка "), // 132
		ERROR_ENTRY(309, "Пустое значение в строке, строка "), //133 
		ERROR_ENTRY(310, "Превышен лимит допустимого значения int, строка "), //134
		ERROR_ENTRY(311, "Тип или количество параметра(ов) в вызываемой функции не соответствует объявленной функции, строка "), //135
		ERROR_ENTRY(312, "Количество параметров в вызываемой функции не соответствует объявленной функции, строка "), //136
		ERROR_ENTRY(313, "Недоступные операции в выражении "), //137
		ERROR_ENTRY(314, "Недопустимый тип идентификатора в условной конструкции, строка "),
		ERROR_ENTRY(315, "Неверная библиотечная функция, строка "),
		




		
		ERROR_ENTRY_NODEF(316),
		ERROR_ENTRY_NODEF(317), ERROR_ENTRY_NODEF(318),ERROR_ENTRY_NODEF(319), ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340),
		ERROR_ENTRY_NODEF10(350),

		ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		//Синтаксис
		ERROR_ENTRY(600, "Неверная структура программы, строка "),
		ERROR_ENTRY(601, "Неверная синтаксическая конструкция, строка "),
		ERROR_ENTRY(602, "Неверное выражение, строка "),
		ERROR_ENTRY(603, "Неверный знак в выражении, строка "),
		ERROR_ENTRY(604, "Неверные параметры функции, строка "),
		ERROR_ENTRY(605, "Неверные параметры вызываемой функции, строка "),
		ERROR_ENTRY(606, "Неверная конструкция условного оператора, строка "),

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
			ERROR err = { errors[id] };
			
			throw err;
			return err;
		}
		else
		{
			ERROR err = { errors[0] };
			
			throw err;
			return err;
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if ((id > 0) && (id < ERROR_MAX_ENTRY))
		{
			ERROR err = { errors[id] };
			
			err.index.line = line;
			err.index.col = col;
			throw err;
			return err;
		}
		else
		{
			ERROR err = { errors[0]};
			for (int i = 0; i < ERROR_MAXSIZE_MESSAGE; i++)
				err.message[i] = errors[0].message[i];
			err.index.line = line;
			err.index.col = col;
			throw err;
			return err;
		}
	}
}
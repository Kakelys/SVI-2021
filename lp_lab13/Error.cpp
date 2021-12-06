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
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113, "������ ��� �������� ����� � ������������� ����� (il.txt)"),
		ERROR_ENTRY(114, "������ 5 �������� � �������������� � ������: "),
		ERROR_ENTRY(115, "Big letter in idenf, line: "),
		ERROR_ENTRY(116, "Idenf matches with keyword, line: "),
		ERROR_ENTRY(117, "� ���������� ������� ������, ������: "),
		ERROR_ENTRY(118, "������ � ��������� �������������� ����� ��������, ������: "),
		ERROR_ENTRY(119, "� �������������� ��������� �� ������, ������: "),
		ERROR_ENTRY(120, "�������� �������� ����� ��� �������������, ������: "),
		ERROR_ENTRY(121, "��� ������� � ������������ ���������� �� ���������, ������: "),
		ERROR_ENTRY(122, "�� ������� �� ���� ���������� �������, ����������� � ��������������, ������: "),
		ERROR_ENTRY(123, "data types of right and left part non equal, line: "),
		ERROR_ENTRY(124, "Text after ; , ������: "),
		ERROR_ENTRY(125, "������ ����������  , ������: "),
		ERROR_ENTRY(126, "Failed to create Polish Notation , line: "),
		ERROR_ENTRY(127, "More than one main"),
		ERROR_ENTRY(130, "Lex Table"),
		ERROR_ENTRY(600, "�������� ��������� ���������"),
		ERROR_ENTRY(601, "��������� ��������"),
		ERROR_ENTRY(602, "������ � ���������"),
		ERROR_ENTRY(603, "������ � ���������� �������"),
		ERROR_ENTRY(604, "������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
	};
	ERROR geterror(int id)
	{
		if ((id > 0) && (id < ERROR_MAX_ENTRY))
		{
			ERROR err = { errors[id-2].id };
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
			ERROR err = { errors[id].id };
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
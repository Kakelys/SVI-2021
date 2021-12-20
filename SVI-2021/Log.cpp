#include "stdafx.h"
#include <wchar.h>
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "FST.h"
#include <fstream>
#include <ctime>
#include "Log.h"

namespace Log {
	LOG getlog(wchar_t logfile[]) {
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open()) { throw ERROR_THROW(112); }
		wcscpy_s(log.logfile, logfile);
		return log;
	}


	void WriteLine(LOG log, std::string c, ...) {
		std::string fullstr = "";
		std::string* p = &c;
		int i = 0;
		while (p->size() < 500) {

			fullstr += *p;
			p++;
		}
		*log.stream << fullstr;
	}
	void WriteLexResult(LOG log, IT::IdTable idenfs, LT::LexTable lexems) 
	{
		std::string info = "===============Таблица Лексем===============\n";
		//Часть для Лекс.
		int curLine = 1;
		LT::Entry lexem;
		for (int i = 1; i < lexems.size + 1; i++)
		{
			lexem = LT::GetEntry(lexems, i);

			info += "|" + lexem.lexema + "| line - " + std::to_string(lexem.linenumber) + "| index Ti - " + std::to_string(lexem.indexTI) + "|\n";
		}

		*log.stream << info;
		info = "===============Таблица Идентификаторов===============\n";

		//Часть для иденфов
		IT::Entry idenf;
		for (int i = 1; i < idenfs.size + 1; i++)
		{
			idenf = IT::GetEntry(idenfs, i);

			info +=
				 "  name - " + idenf.name
				+ "  type - " + std::to_string(idenf.type)
				+ "  datatype - " + std::to_string(idenf.datatype)
				+ " ParmCount - " + std::to_string(idenf.ParmCount)
				+ " value - ";

			switch (idenf.datatype)
			{
			case 1:
				info += std::to_string(idenf.value.vint);
				break;


			case 2:
				for (int j = 0; j < idenf.value.vstr->len && (int)idenf.value.vstr->str[j] != -52; j++)
				{
					info+= idenf.value.vstr->str[j];
				}
				break;
			}

			info+= "\n";

		}

		*log.stream << info;
		info = "";
	}
	void WriteSintxResult(LOG log, MFST::Mfst mfst) 
	{

		char rbuf[205];
		MFST::MfstState state;
		GRB::Rule rule;
		std::string info = "================Дерево разбора==============\n";
		for (unsigned short k = 0; k < mfst.storestate.size(); k++)
		{
			state = mfst.storestate.c[k];
			rule = mfst.grebach.getRule(state.nrule);
			info +=  std::to_string(state.lenta_position) + ": "
				 + rule.getCRule(rbuf, state.nrulechain)
				+ "\n";
		}
		*log.stream << info;
	//	std::cout << info;
	}

	void WriteLine(LOG log, char* c, ...) {
		char str[900];
		strcpy(str, "");
		char** p = &c;
		while (*p != "") {
			strcat(str, *p);
			strcat(str, " ");
			p++;
		}
		*log.stream << str;
		*log.stream << "\n";
	}
	void WriteLog(LOG log) {
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		*log.stream << "--------Протокол-------" << "Дата: " << asctime(timeinfo);
	}
	void WriteParm(LOG log, Parm::PARM parm) {
		*log.stream << "----Параметры----\n";
		char* str = new char[900];
		wcstombs(str, parm.in, 900);
		*log.stream << "-in:" << str << "\n";
		wcstombs(str, parm.out, 900);
		*log.stream << "-out:" << str << "\n";
		wcstombs(str, parm.log, 900);
		*log.stream << "-log:" << str << "\n";
	}

	void WriteIn(LOG log, In::IN in) {
		*log.stream << "--- Исходные данные ---\n"
			<< "Всего символов: " << in.size << "\n"
			<< "Всего строк: " << in.lines << "\n"
			<< "Пропущено " << in.ignor << "\n";

	}
	void WriteError(LOG log, Error::ERROR error) {
		*log.stream << "Ошибка " << error.id << ": " << error.message;
		if (error.index.line > 0) {
			*log.stream << error.index.line << "\n\n";
		}
		else {
			*log.stream << "\n\n";
		}
	}


	void Close(LOG log) {
		//*log.stream << "\n\n\n\n\n" << "Если ошибки нет и она была в parm, то ищи crash_logs.log";
		log.stream->close();
	}
	


}

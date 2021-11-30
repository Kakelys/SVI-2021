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


	void WriteLine(LOG log, wchar_t* c, ...) {
		wchar_t fullstr[900] = L"";
		char* str = new char[900];
		wchar_t** p = &c;
		while (*p != L"") {
			wcsncat_s(fullstr, *p, 900);
			wcsncat_s(fullstr, L" ", 900);
			p++;
		}
		wcstombs(str, fullstr, 900);
		*log.stream << str;
		*log.stream << "\n";
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
		*log.stream << "Error " << error.id << ": " << error.message;
		if (error.index.line > 0) {
			*log.stream << error.index.line << "\n\n";
		}
		else {
			*log.stream << "\n\n";
		}
	}


	void Close(LOG log) {
		*log.stream << "\n\n\n\n\n" << "Если ошибки нет и она была в parm, то ищи crash_logs.log";
		log.stream->close();
	}
	


}

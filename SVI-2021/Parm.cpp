#include "stdafx.h"
#include <fstream>
#include <string>
#include "In.h"
#include "Error.h"
#include "FST.h"
using namespace std;
namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		setlocale(LC_ALL, "RUS");
		PARM prm = {};
		//wcscpy_s(prm.in, *argv);
		wchar_t str[900];
		wchar_t fullstr[900] = L"";
		wchar_t findin[] = L"-in:";
		wchar_t findout[] = L"-out:";
		wchar_t findlog[] = L"-log:";
		wchar_t founded[900] = L"";
		wchar_t space[] = L" ";
		wchar_t isForm[] = L"-c";


		for (int i = 1; i < argc; i++) {
			wcscpy_s(str, argv[i]);
			wcsncat_s(fullstr, str, PARM_MAX_SIZE);
			wcsncat_s(fullstr, L" ", PARM_MAX_SIZE);
		}


	
		//Определение, запускается ли с помощью формы
		if (wcsstr(fullstr, isForm) > 0) { prm.isForm = true; }
		


		// Поиск/Создание in
		if (wcsstr(fullstr, findin) == NULL) { throw ERROR_THROW(100); }
		else {
			int counter = 0;
			wcscpy_s(founded, wcsstr(fullstr, findin));
			for (int i = 4, j = 0; i < std::wcslen(founded); i++, j++) {
				counter++;
				if (founded[i + 1] == space[0]) break;

			}
			if ((counter + 4) >= PARM_MAX_SIZE) { throw ERROR_THROW(104); }
			wcscpy_s(founded, wcsstr(fullstr, findin));
			for (int i = 4, j = 0; i < std::wcslen(founded); i++, j++) {
				prm.in[j] = founded[i];
				if (founded[i + 1] == space[0]) break;

			}
			//debug in
			//std::wcout << L"Полученное In " << prm.in << "\n\n";
		}

		// Поиск/Создание out
		if (wcsstr(fullstr, findout) == NULL) {
			wcsncat_s(prm.out, prm.in, PARM_MAX_SIZE);
			wcsncat_s(prm.out, L"out.asm", PARM_MAX_SIZE);
			//debug out
			//std::wcout << L"Полученное out " << prm.out << "\n\n";
		}
		else {

			int counter = 0;
			wcscpy_s(founded, wcsstr(fullstr, findout));
			for (int i = 5, j = 0; i < std::wcslen(founded); i++, j++) {
				counter++;
				if (founded[i + 1] == space[0]) break;

			}


			if ((counter + 5) >= PARM_MAX_SIZE) { throw ERROR_THROW(104); }
			wcscpy_s(founded, wcsstr(fullstr, findout));
			for (int i = 5, j = 0; i < std::wcslen(founded); i++, j++) {
				prm.out[j] = founded[i];
				if (founded[i + 1] == space[0]) break;

			}
			//debug out
			//std::wcout << L"Полученное out " << prm.out << "\n\n";
		}



		// Поиск/Создание log
		if (wcsstr(fullstr, findlog) == NULL) {
			wcsncat_s(prm.log, prm.in, PARM_MAX_SIZE);
			wcsncat_s(prm.log, L".log", PARM_MAX_SIZE);
			//debug log
			//std::wcout << L"Полученное log " << prm.log << "\n\n";
		}
		else {
			int counter = 0;
			wcscpy_s(founded, wcsstr(fullstr, findlog));
			for (int i = 5, j = 0; i < std::wcslen(founded); i++, j++) {
				counter++;
				if (founded[i + 1] == space[0]) break;

			}
			if ((counter + 5) >= PARM_MAX_SIZE) { throw ERROR_THROW(104); }
			wcscpy_s(founded, wcsstr(fullstr, findlog));
			for (int i = 5, j = 0; i < std::wcslen(founded); i++, j++) {
				prm.log[j] = founded[i];
				if (founded[i + 1] == space[0]) break;

			}
			//debug log
			//std::wcout << L"Полученное log " << prm.log << "\n\n";
		}
		return prm;
	}
}
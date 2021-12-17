#include "stdafx.h"
#include <iostream>



#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "LEX.h"
#include "PN.h"
#include "GRB.h"
#include "MFST.h"
#include "SEM.h"
#include "GEN.h"
#include "LIB.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	setlocale(LC_ALL, ".1251");
	


	Log::LOG log = Log::INITLOG;
	bool logcreate = false;				//Если лог файл не был создан или указан, то при ошибке создастся crash_logs
	try
	{
		
		
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::getin(parm.in, parm.out);
		LT::LexTable lexems = LT::Create(LT_MAXSIZE);
		IT::IdTable idenfs = IT::Create(IT_MAXSIZE);
		LIB::LibTable lib = LIB::Create(MAX_LIB);
		LIB::AddSomeFunc(lib);
		log = Log::getlog(parm.log); logcreate = true;

		
		

		


		
		
		LEX::lexTable(parm.out, idenfs, lexems); // Лекс.анализатор, создние таблицы лексем и идентификаторов
		Log::WriteLine(log, "Лексический анализатор успешно завершил работу\n");
		Log::WriteLexResult(log, idenfs, lexems);


#ifdef DISPLAY

		std::cout << "\n\n\n";
		LEX::DisplayLT(lexems);//Вывод таблицы лексем
		std::cout << "\n\n\n\n\n";


		LEX::DisplayIT(idenfs);//Вывод таблицы идентификаторов
		std::cout << "\n\n\n\n";
		std::cout << "\n\n\n\n";
#endif

		


				//Синтаксический анализатор
#ifdef DEBUG
		MFST_TRACE_START
#endif

			MFST::Mfst mfst(lexems, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		//mfst.printrules();
		Log::WriteLine(log, "\n\n\nСинтаксический анализатор успешно завершил работу\n");
		Log::WriteSintxResult(log, mfst);



		SEM::CheckSemantics(idenfs, lexems,lib);//Семантический анализатор
		Log::WriteLine(log, "\n\n\nСемантический анализатор успешно завершил работу\n");
		

		

		PN::PolishNT(parm.in, lexems, idenfs); //Польская запись
		std::cout << "\n\n\n";
		LEX::DisplayLT(lexems);//Вывод таблицы лексем
		std::cout << "\n\n\n\n\n";

		//Генерация кода
		GEN::CodeGeneration(lexems, idenfs,lib);
		



		







		
		

		
		Log::Close(log);


		//Запуск bat файла, который по итогу запускает ассемблерный код
		system("start C:\\papka\\programms\\Git\\SVI-2021\\compile.bat");
	}
	catch (Error::ERROR e)
	{
		
		if (logcreate == false) {
			wchar_t str[] = L"crash_logs.log";
			log = Log::getlog(str); logcreate = true;
		}
		
		Log::WriteLine(log, "\n\n\n================ERORR MESSAGE=================\n\n\n");
		Log::WriteError(log, e);
		Log::WriteLine(log, "\n\n================ERORR MESSAGE=================\n\n\n");


		Log::Close(log);
#ifdef DISPLAY
		std::cout << "Error " << e.id << ":" << e.message << e.index.line;
#endif // DEBUG

		system("start C:\\papka\\programms\\Git\\SVI-2021\\error.bat");
		
	}

	return 0;
		
}





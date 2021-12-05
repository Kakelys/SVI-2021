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
#include "ILG.h"
#include "GEN.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	setlocale(LC_ALL, ".1251");
	//setlocale(LC_ALL, "rus");


	Log::LOG log = Log::INITLOG;
	bool logcreate = false;				//Если лог файл не был создан или указан, то при ошибке создастся crash_logs
	try
	{

		

		Parm::PARM parm = Parm::getparm(argc, argv);
		In::getin(parm.in, parm.out);
		LT::LexTable lexems = LT::Create(LT_MAXSIZE);
		IT::IdTable idenfs = IT::Create(IT_MAXSIZE);
		
		
		LEX::lexTable(parm.out, idenfs, lexems);



		PN::PolishNT(parm.in,lexems,idenfs);


		std::cout << "\n\n\n";
		LEX::DisplayLT(lexems);
		std::cout << "\n\n\n\n\n";


		LEX::DisplayIT(idenfs);
		std::cout << "\n\n\n\n";
		std::cout << "\n\n\n\n";


		//Генерация кода
		GEN::CodeGeneration(lexems, idenfs);
		// 
		//Промежуточный код, который я не доделал и по итогу не использовал, bruh
		//ILG::Gen(lexems, idenfs);




		//Display part
	
				//Костыль под симантический анализатор, надо обновить Грейбаха перед удалением
	/*	for (int k = 1; k < lexems.size + 1; k++)
		{
			if (lexems.table[k - 1].lexema == "+" || lexems.table[k - 1].lexema == "-" || lexems.table[k - 1].lexema == "*" || lexems.table[k - 1].lexema == "/")
			{
				lexems.table[k - 1].lexema = "v";
			}
		}*/





		//



		//Синтаксис
		/*MFST_TRACE_START
			MFST::Mfst mfst(lexems, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();*/







		system("start C:\\papka\\programms\\Git\\SVI-2021\\compile.bat");
	}
	catch (Error::ERROR e)
	{
		
		if (logcreate == false) {
			wchar_t str[] = L"crash_logs.log";
			log = Log::getlog(str); logcreate = true;
		}
		if (e.index.line > 0) { Log::WriteError(log, e); }
		else 
		{
			Log::WriteError(log, e);
		}
		return 13;
	}


	return 0;
		
}





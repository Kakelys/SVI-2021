#include "stdafx.h"
#include "ILG.h"



namespace ILG 
{

	void Gen(LT::LexTable& lexems, IT::IdTable& idenfs) 
	{
		LT::LexTable lxs = LT::Create(LT_MAXSIZE);

		int maintype = 0;
		int start, end;
		int funccounter = 0;
		for (int i = 1; i < lexems.size + 1; i++) 
		{
			//Нахождение выражения для упрощения
			if (lexems.table[i-1].lexema == "=") 
			{
				maintype = idenfs.table[lexems.table[i - 2].indexTI].datatype;
				start = i; 
				i++;
				//Пока не дойдёт до null
				while (lexems.table[i - 1].lexema != "A" && i !=lexems.size)
				{
					i++;
				}
				end = i;

				//Временная лексическая таблица, которая хранит само выражение 
				LT::LexTable tempLxs = LT::Create(end - start + 1);
			    std::string arifms = "";
				for (int j = start + 1; j < end; j++) 
				{
					if (lexems.table[j - 1].lexema == "l" || lexems.table[j - 1].lexema == "i") {
						LT::Add(tempLxs, lexems.table[j - 1]);
					}
					else 
					{
						arifms += lexems.table[j - 1].lexema;
					}
					//std::cout << lexems.table[j - 1].lexema;

				}				
				//дополнительные объявления 
				
				std::string fun;
				int dtAmount = tempLxs.size / 2;
				//Найти, в какой функции находится выражение
				if (dtAmount % 2 == 0)
				{
					fun = IT::GetLastFunc(idenfs, lexems, dtAmount * 2+tempLxs.size);

				}
				else
				{
					
					fun = IT::GetLastFunc(idenfs, lexems, dtAmount *2+1+tempLxs.size);
				}
				//Добавление dti; если оно требуется
				for (int k = tempLxs.size / 2; k >0;k--) 
				{
					funccounter++;
					
					//find i and put in idenfs
					IT::Entry idenf = k % 2 == 0 ? idenfs.table[tempLxs.table[k * 2-1].indexTI] : idenfs.table[tempLxs.table[k * 2 + 1-1].indexTI];
					idenf.name = fun + std::to_string(funccounter);
					idenf.type = 1;
					idenf.datatype = maintype;
					IT::Add(idenfs, idenf);

					LT::Entry lexem;
					//d in lex
					lexem.lexema = LEX_DECLARE;
					lexem.linenumber = k%2==0? tempLxs.table[k*2].linenumber : tempLxs.table[k * 2+1-1].linenumber;
					lexem.indexTI = LT_TI_NULLIDX;
					LT::Add(lxs, lexem);
					//t in lex
					lexem.lexema = LEX_INTEGER;
					lexem.linenumber = k % 2 == 0 ? tempLxs.table[k * 2].linenumber : tempLxs.table[k * 2 + 1-1].linenumber;
					lexem.indexTI = LT_TI_NULLIDX;
					LT::Add(lxs, lexem);
					//i in lex
					lexem.lexema = LEX_ID;
					lexem.linenumber = k % 2 == 0 ? tempLxs.table[k * 2].linenumber : tempLxs.table[k * 2 + 1-1].linenumber;
					lexem.indexTI = idenfs.size-1;
					LT::Add(lxs, lexem);
					//; in lex
					lexem.lexema = LEX_SEMICOLON;
					lexem.linenumber = k % 2 == 0 ? tempLxs.table[k * 2].linenumber : tempLxs.table[k * 2 + 1-1].linenumber;
					lexem.indexTI = LT_TI_NULLIDX;
					LT::Add(lxs, lexem);
				}
				std::cout << "\n\n\n";
				LEX::DisplayLT(lxs);

				
			} 
			if (lexems.table[i].lexema == "=") { continue; }
			LT::Add(lxs, lexems.table[i - 1]);
		
		}

	
	}

}
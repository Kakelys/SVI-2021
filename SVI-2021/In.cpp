#include "stdafx.h"
#include <string>
#include "Log.h"
#include "In.h"
#include "Error.h"
#include "FST.h"


namespace In
{
	int zs;
	int snl;
	int rng;
	void getin(wchar_t infile[]) // delete outfile and put il.txt for find some errors
	{
		setlocale(LC_CTYPE, ".1251");
		IN inn;
		inn.size = 0;
		inn.lines = 1;
		inn.ignor = 0;
		unsigned short position = 0;
		wchar_t out[] = L"il.txt";


		std::fstream input; input.open(infile, std::ios::in);
		if (!input) { throw ERROR_THROW(200) }
		char letter[1];
		

		
		std::fstream il; 
		il.open(out, std::ios::out);
		if(!il){ throw ERROR_THROW(203); }
		bool findfirstbrackets=false;
		bool findsecondbrackets = false;
		char bracket[2] = "'";
		
		std::string line="";
		std::string first = " \n";
		first += (char)0x95;
		std::string second = "\n";
		second += (char)0x95;

		while (!input.eof())
		{
			char ch = input.get();

			if (inn.code[(int)ch + 256] == IN::E) 
			{
				line += letter[0];
				goto ifFindEndOfFile; 
			} //Убирает символ конца файла 
			++zs;
			if (inn.code[(int)ch] == IN::F)
				ERROR_THROW_IN(201, zs, 0);
			if (inn.code[(int)ch+256] == IN::F)
				ERROR_THROW_IN(201, zs, 0);
			if (inn.code[(int)ch] == IN::I) { continue; }
			if (inn.code[(int)ch + 256] == IN::I) { continue; }

			//
			if (ch == '"' && (findfirstbrackets == false || findsecondbrackets == false)) //Ищет строки
			{
				if (findfirstbrackets == true) {
					line += letter[0];
					line += ch;
					findsecondbrackets = true; 
				}
				else {
					findfirstbrackets = true;
					line += letter[0];
					
				}
			}
			else
			{
				if (inn.lines >= 1 && inn.size > 0) {
					if (ch == ' ' && letter[0] == ' ' && findfirstbrackets == false || ch == '\n') // скип пробелов, нет - вывод символа
					{
						if (ch == '\n' && letter[0]==',')  // просто калссная фича
						{

							line += letter[0];
							line += (char)0x95;
							ch = input.get();
							letter[0] = ch;
							continue;

						}
						if (ch == '\n')
						{
							line += letter[0];
							line += (char)0x95;
							std::cout << (char)0x95;
							if (line == first || line == second) { il << (char)0x95; }
							else {
								il << line;
							}
							line = "";
						}
					}
					else
					{
						if (findsecondbrackets == true) //Найденные строки - false
						{
							findfirstbrackets = false;
							findsecondbrackets = false;
						}
						else
						{
							line += letter[0];	
						}
					}
				}
			}
			if (ch != ' ' && letter[0] == '{') { line += " "; }
			letter[0] = ch;
		//



			if ((int)ch >= 0)
			{
				if (inn.code[(int)ch] == IN::T)
				{
					++inn.size;
					if ((ch == '\n') || (ch == '\0')) {
						++inn.lines;
					}
					++position;
				}
			}
			else if ((int)ch < 0)
			{
				if (inn.code[(int)ch + 256] == IN::T)
				{
					++inn.size;
					if ((ch == '\n') || (ch == '\0'))
						++inn.lines;
					++position;
				}
			}

		}
	ifFindEndOfFile:
		il << line;
		il.close();
	}
	
	
	
}
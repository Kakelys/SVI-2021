#include "stdafx.h"
#include <fstream>
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
	void getin(wchar_t infile[],  wchar_t outfile[]) // delete outfile and put il.txt for find some errors
	{
		setlocale(LC_CTYPE, ".1251");
		IN inn;
		inn.size = 0;
		inn.lines = 1;
		inn.ignor = 0;
		unsigned short position = 0;
		wchar_t out[] = L"il.txt";


		std::fstream input; input.open(infile, std::ios::in);
		if (!input) { throw ERROR_THROW(110) }
		char letter[1];
		

		
		std::fstream il; 
		il.open(out, std::ios::out);
		if(!il){ throw ERROR_THROW(112); }
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

			if (inn.code[(int)ch + 256] == IN::I) 
			{
				goto ifFindEndOfFile; 
			} //Убирает символ конца файла 
			++zs;
			if (inn.code[(int)ch] == IN::F)
				ERROR_THROW_IN(111, zs, 0);
			if (inn.code[(int)ch+256] == IN::F)
				ERROR_THROW_IN(111, zs, 0);
			if ((int)ch >= 0)
			{
				if (inn.code[(int)ch] == IN::I)
					++inn.ignor;
			}
			else if ((int)ch < 0)
			{
				if (inn.code[(int)ch + 256] == IN::I)
					++inn.ignor;
			}

			//
			if (ch == 0x27 && (findfirstbrackets == false || findsecondbrackets == false)) //Ищет строки
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
	
	
	void getILfile(wchar_t outfile[])
	{
		std::fstream input; input.open("il.txt", std::ios::in);
		if (!input) { throw ERROR_THROW(113) }
		std::string line;
		std::string word;
		std::string Idenf; Idenf.clear(); // очистка строки

		std::string alphabet = "qwertyuiopasdfghjklzxcvbnm";
		wchar_t out[] = L"IdenfTable.txt";
		std::fstream idenffile;
		//очистка файла 
		idenffile.open(out, std::ios::out);
		idenffile.close();
		//

		idenffile.open(out, std::ios::app);

		int numb_of_line = 0;
		int counter_idenf_in_one_line;
		idenffile << line;
		int typeofdata;
		int typeofidenf;
		std::string valueofidenf;
		bool IsItLetter = false;

		int scope = 0; 
		int maxscope = 0;
		int functionopen = 0;
		int functionclose = 0;
		int i = 0;
		int forcheck=0;
		int sepcount = 0;
		int positioninline;
		int sepline = 0;
		while (std::getline(input, line)) {
			Idenf = "";
			positioninline = 0;
			std::string nosep = "";
			sepcount = 0;
			valueofidenf = "";
			int counter_idenf_in_one_line = 0;
			numb_of_line += 1;
			//Массив позиций сепараторов и зануление сепараторов после создания массива
			for (int j=0; j < line.length(); j++) 
			{
				if (line[j] == (char)0x95) 
				{
					sepcount++;
				}		
			}
			int *separators = new int[sepcount];
			for (int j = 0,k=0; j < line.length(); j++)
			{
				if (line[j] == (char)0x95)
				{
					separators[k] = j + 1;
					k++;
				}
				else { nosep += line[j]; }
			}
			line = nosep;
			//nosep из-за того, что replace не может изменить длину строки
			/////
	

			std::stringstream streamLine;
			streamLine << line;
			streamLine >> word;
			positioninline += word.length() + 1;
			//Надо потом убрать лишние пробелы из il.txt
			/*if (line == " " || line == "")
			{
				sepline += sepcount;
				continue; 
			}*/
			if (word == "{") 
			{
				streamLine >> word; 
				positioninline += word.length() + 1;
			}
			if (line.find("{") <256 && line.length() <= 3)
			{ 
				sepline += sepcount;
				continue; 
			}
			if (line.find("};") < 256 || line.find("} ;") < 256 || line.find("}") <256)
			{
				
				if (line == "};" || line == "} ;" || line == "}")
				{
					sepline += sepcount;
					functionclose += 1;
					
					continue;
				}
				else if (word == "};" || word == "} ;") 
				{
					functionclose += 1;
					streamLine >> word;
					positioninline += word.length() + 1;
				}
				else 
				{
					{ ERROR_THROW_IN(119, sepline+separat(separators, sepcount, positioninline), 0); }
				}
			
			}
			//			номер строки|название|тип(1/2)1-int/2-str|тип иденфа(1/2/3/4)1-переменная/2-функция/3-параметр/4-литерал|номер иденфа в строке|v-значение, если есть
			// Пометка для создания файла с идентификаторами: 0000|i_xxxxx|d_0|t_0|a_00|v_?|
			//													(если меньше 5 x, то доставить пробелы)
			if (word == "integer" || word == "string") // for data type
/*int\str*/ {
////////////
				if (word == "integer") { typeofdata = 1; }
				else { typeofdata = 2; }
				streamLine >> word;
				positioninline += word.length() + 1;
				if (word == "function") 
				{
					functionopen = +1;
					typeofidenf = 2;
					valueofidenf = "f";
					streamLine >> word;
					positioninline += word.length() + 1;
					maxscope += 1;
					scope = maxscope;
					//поиск идентефикатора
					i = 0;
					IsItLetter = false;
					for (; i < 10; i++)
					{
						if (i == word.length()) { break; }
						for (int j = 0; j < alphabet.length(); j++) {
							if (word[i] == alphabet[j]) { IsItLetter = true; }
						}
						if (word[i] == ' ') { break; }
						if (word[i] == '(') { break; }
						if (word[i] == tolower(word[i])) 
						{
							if (IsItLetter == false) { { ERROR_THROW_IN(119,sepline +separat(separators, sepcount, positioninline), 0); } }
							Idenf += word[i];
							IsItLetter = false;
						}
						else 
						{
							ERROR_THROW_IN(115,sepline +separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
						}
						
					}
					positioninline += Idenf.length();
					if (Idenf.length()>5) { ERROR_THROW_IN(114, +separat(separators, sepcount, positioninline), 0);}//throw if big letter in indenf
					if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116, sepline +separat(separators, sepcount, positioninline), 0); }//throw if key word
					if (word.find("(")>256) 
					{ 
						streamLine >> word; 
						positioninline += word.length() + 1;
						positioninline += word.length() + 1;
						if (word.find("(") > 256) {
							ERROR_THROW_IN(118, sepline +separat(separators, sepcount, positioninline), 0);
						}
					} //Пробел или другой символ в идентефикаторе

					//конец поиска идентификатора
					counter_idenf_in_one_line += 1;

					// Запись найденного идентификатора в файл
					if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
					else { 
						if(numb_of_line < 100)
						{
							idenffile << "00" << numb_of_line << "|";
						}
						else 
						{
							if (numb_of_line < 1000) { idenffile << "0" << numb_of_line << "|";
							}
							else 
							{
							if(numb_of_line < 10000) { idenffile << numb_of_line << "|";
							}
							}
						}
					}
					idenffile << Idenf;
					for (int j = Idenf.length(); j < 5; j++) 
					{
						idenffile << " ";
					}
					idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
					if (counter_idenf_in_one_line < 10) 
					{
						idenffile << "0" << counter_idenf_in_one_line;
					}
					else 
					{
						idenffile << counter_idenf_in_one_line;
					}
					if (scope < 10) { idenffile << "|l_0" << scope; }
					else { idenffile << "|l_" << scope; }
					idenffile << "|" << "v_" << valueofidenf << "\n";
					Idenf = ""; // clear idenf for next idenf
					//конец записи в файл
					valueofidenf = "";

					// Работа в скобках функции по поиску типа ////////////////////////////////////////
					functionbrackets: 
					if (word.find("integer") < 256) 
					{
					// поиск того, что после integer пробел| длина строки - начальный вход = 7, т.е. длине слова integer
						if ((word.length() - word.find("integer")) == 7) { typeofdata = 1; }
						else 
						{
						//Ошибка в параметрах функции
							ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
						}

					}
					else 
					{
						if (word.find("string") < 256) 
						{
							// поиск того, что после string пробел длина строки - начальный вход = 6, т.е. длине слова string
							if ((word.length() - word.find("string")) == 6) { typeofdata = 2; }
							else 
							{
								ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
							}
						}
						else  //Посмотреть, есть ли в некст слове из потока есть тип данных, если нет, то ошибка
						{
							streamLine >> word;
							positioninline += word.length() + 1;
							if (word.find("integer") < 256) 
							{
								if ((word.length() - word.find("integer")) == 7) { typeofdata = 1; }
								else
								{
									//Ошибка в параметрах функции
									ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
								}
							}
							else 
							{
								if (word.find("string") < 256) 
								{
									if ((word.length() - word.find("string")) == 6) { typeofdata = 2; }
									else {
										ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
									}
								}
								else 
								{
									ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
								}
							}
						
						}
					}
					//Поиск идентификатора после типа и запись в файл
					typeofidenf = 3;
					streamLine >> word;
					positioninline += word.length() + 1;
					
					//поиск идентефикатора
					i = 0;
					IsItLetter = false;
					for (; i < 10; i++)
					{
						if (i == word.length()) { break; }
						for (int j = 0; j < alphabet.length(); j++) {
							if (word[i] == alphabet[j]) { IsItLetter = true; }
						}
						if (word[i]== ',') { break; }
						if (word[i] == ' ') { break; }
						if (word[i] == ')') { break; }
						if (word[i] == tolower(word[i]))
						{
							if (IsItLetter == false) { ERROR_THROW_IN(119, sepline + separat(separators, sepcount, positioninline), 0);  }
							Idenf += word[i];
							IsItLetter = false;
						}
						else
						{
							ERROR_THROW_IN(114, sepline + separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
						}

					}
					positioninline += Idenf.length();
					if (Idenf.length()>5) { ERROR_THROW_IN(114, sepline + separat(separators, sepcount, positioninline), 0); }//throw if letter > 5
					if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116, sepline + separat(separators, sepcount, positioninline), 0); }//throw if key word
					//конец поиска идентификатора
					counter_idenf_in_one_line += 1;
					// Запись найденного идентификатора в файл
					if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
					else {
						if (numb_of_line < 100)
						{
							idenffile << "00" << numb_of_line << "|";
						}
						else
						{
							if (numb_of_line < 1000) {
								idenffile << "0" << numb_of_line << "|";
							}
							else
							{
								if (numb_of_line < 10000) {
									idenffile << numb_of_line << "|";
								}
							}
						}
					}
					idenffile << Idenf;
					for (int j = Idenf.length(); j < 5; j++)
					{
						idenffile << " ";
					}
					idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
					if (counter_idenf_in_one_line < 10)
					{
						idenffile << "0" << counter_idenf_in_one_line;
					}
					else
					{
						idenffile << counter_idenf_in_one_line;
					}
					if (scope < 10) { idenffile << "|l_0" << scope; }
					else { idenffile << "|l_" << scope; }
					idenffile << "|" << "v_" << valueofidenf << "\n";
					 // clear idenf for next idenf
					//конец записи в файл

					if (word.find(",") < 256) { Idenf = ""; goto functionbrackets; }
					else
					{
						streamLine >> word;
						positioninline += word.length() + 1;
						if (word.find(",") < 256) { Idenf = ""; goto functionbrackets; }
					
					}



						//Поиск ) в конце параметров перед ними и после не должно быть лишнего текста
						if (line.find(Idenf)+Idenf.length()==line.find(")")|| line.find(Idenf) + Idenf.length()+1 == line.find(")"))
						{
							
						}
						else {
						ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);

						}
						if (line.find("{") < 256) 
						{
							if (line.length() == line.find("{")+2||line.length()-1 == line.find("{") || (line.find(")") + 2 == line.find("{") && line[line.find(")") + 1] == line.find(' ')))
							{
							}
							else 
							{
								ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0);
							}
						}
						else
						{
							if (line.find(")") == line.length()-1 || line.find(")")+2 == line.length()) {}
							else { 
								ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
						}
					
					Idenf = "";
					sepline += sepcount;
					continue;
				}
				else
				{
					
				ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0);
						//function missed or wrong word
					
					
				}
			}
			else
			{
/*declare*/
/*////////////*/if (word == "declare")
				{
					streamLine >> word;
					positioninline += word.length() + 1;
					if (word == "integer" || word == "string") 
					{
						if (word == "integer") { typeofdata = 1; }
						if (word == "string") { typeofdata = 2; }
						streamLine >> word;
						positioninline += word.length() + 1;

						if (word == "function") {
							valueofidenf = "d";
							counter_idenf_in_one_line = 0;
							//поиск идентефикатора
							streamLine >> word;
							positioninline += word.length() + 1;
							typeofidenf = 2;
							i = 0;
							IsItLetter = false;
							for (; i < 10; i++)
							{
								if (i == word.length()) { break; }
								for (int j = 0; j < alphabet.length(); j++) {
									if (word[i] == alphabet[j]) { IsItLetter = true; }
								}
								if (word[i] == '(') { break; }
								if (word[i] == ' ') { break; }
								if (word[i] == tolower(word[i]))
								{
									if (IsItLetter == false) { ERROR_THROW_IN(119,sepline+separat(separators, sepcount, positioninline), 0); }
									Idenf += word[i];
									IsItLetter = false;
								}
								else
								{
									ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
								}

							}
							positioninline += Idenf.length();
		

							if(Idenf == "substr" || Idenf == "strlen"){}
							else { ERROR_THROW_IN(122,sepline+separat(separators, sepcount, positioninline), 0);}
							std::string amountParam;
							std::string fun = Idenf;
							std::string pastIdenf;
							//встроенные функции 
							counter_idenf_in_one_line += 1;
							int substr[] = { 2,2,1,1 };
							int strlen[] = { 1,2 };
							if (fun == "substr") 
							{
								if (substr[counter_idenf_in_one_line - 1] == typeofdata) {}
								else { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }

								amountParam = "4"; 
							}
							if (fun == "strlen") { 
								if (strlen[counter_idenf_in_one_line - 1] == typeofdata) {}
								else { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
								
								amountParam = "2";
							}
							
							//конец поиска иденфа

								// Запись найденного идентификатора в файл
							if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
							else {
								if (numb_of_line < 100)
								{
									idenffile << "00" << numb_of_line << "|";
								}
								else
								{
									if (numb_of_line < 1000) {
										idenffile << "0" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 10000) {
											idenffile << numb_of_line << "|";
										}
									}
								}
							}
							idenffile << Idenf;
							for (int j = Idenf.length(); j < 5; j++)
							{
								idenffile << " ";
							}
							idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
							if (counter_idenf_in_one_line < 10)
							{
								idenffile << "0" << counter_idenf_in_one_line;
							}
							else
							{
								idenffile << counter_idenf_in_one_line;
							}
							if (scope < 10) { idenffile << "|l_0" << scope; }
							else { idenffile << "|l_" << scope; }
							idenffile << "|" << "v_" << valueofidenf << "\n";
							valueofidenf = "";
						    //конец записи в файл
							Idenf = ""; 	// clear idenf for next idenf

							for (int j = 1; j < atoi(amountParam.c_str()); j++) 
							{
							
							
								if (word.find("integer") < 256)
								{
									// поиск того, что после integer пробел| длина строки - начальный вход = 7, т.е. длине слова integer
									if ((word.length() - word.find("integer")) == 7) { typeofdata = 1; }
									else
									{
										//Ошибка в параметрах функции
										ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);
									}

								}
								else
								{
									if (word.find("string") < 256)
									{
										// поиск того, что после string пробел длина строки - начальный вход = 6, т.е. длине слова string
										if ((word.length() - word.find("string")) == 6) { typeofdata = 2; }
										else
										{
											ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);
										}
									}
									else  //Посмотреть, есть ли в некст слове из потока есть тип данных, если нет, то ошибка
									{
										streamLine >> word;
										positioninline += word.length() + 1;
										if (word.find("integer") < 256)
										{
											if ((word.length() - word.find("integer")) == 7) { typeofdata = 1; }
											else
											{
												//Ошибка в параметрах функции
												ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);
											}
										}
										else
										{
											if (word.find("string") < 256)
											{
												if ((word.length() - word.find("string")) == 6) { typeofdata = 2; }
												else {
													ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);
												}
											}
											else
											{
												ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);
											}
										}

									}
								}
								//Поиск идентификатора после типа и запись в файл
								typeofidenf = 3;
								streamLine >> word;
								positioninline += word.length() + 1;

								//поиск идентефикатора
								i = 0;
								IsItLetter = false;
								for (; i < 10; i++)
								{
									if (i == word.length()) { break; }
									for (int j = 0; j < alphabet.length(); j++) {
										if (word[i] == alphabet[j]) { IsItLetter = true; }
									}
									if (word[i] == ',') { break; }
									if (word[i] == ' ') { break; }
									if (word[i] == ')') { break; }
									if (word[i] == tolower(word[i]))
									{
										if (IsItLetter == false) { ERROR_THROW_IN(119,sepline+separat(separators, sepcount, positioninline), 0); }
										Idenf += word[i];
										IsItLetter = false;
									}
									else
									{
										ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
									}

								}
								positioninline += Idenf.length() ;
								if (Idenf.length() > 5) { ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0); }//throw if letter > 5
								if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116,sepline+separat(separators, sepcount, positioninline), 0); }//throw if key word
								//конец поиска идентификатора
								counter_idenf_in_one_line += 1;

								//проверка на правильность типа, иф нет - ошибочка
								if (fun == "substr")
								{
									if (substr[counter_idenf_in_one_line - 1] == typeofdata) {}
									else { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }

									amountParam = "4";
								}
								if (fun == "strlen") {
									if (strlen[counter_idenf_in_one_line - 1] == typeofdata) {}
									else { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }

									amountParam = "2";
								}



								// Запись найденного идентификатора в файл
								if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
								else {
									if (numb_of_line < 100)
									{
										idenffile << "00" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 1000) {
											idenffile << "0" << numb_of_line << "|";
										}
										else
										{
											if (numb_of_line < 10000) {
												idenffile << numb_of_line << "|";
											}
										}
									}
								}
								idenffile << Idenf;
								for (int j = Idenf.length(); j < 5; j++)
								{
									idenffile << " ";
								}
								idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
								if (counter_idenf_in_one_line < 10)
								{
									idenffile << "0" << counter_idenf_in_one_line;
								}
								else
								{
									idenffile << counter_idenf_in_one_line;
								}
								if (scope < 10) { idenffile << "|l_0" << scope; }
								else { idenffile << "|l_" << scope; }
								idenffile << "|" << "v_" << valueofidenf << "\n";
								// clear idenf for next idenf
							   //конец записи в файл
								if (typeofdata == 1) 
								{
									pastIdenf = "integer " + Idenf;
								}
								else 
								{
									pastIdenf = "string " + Idenf;
								}
								if (word.find(",") < 256) { Idenf = ""; continue; }
								else {
									streamLine >> word;
									positioninline += word.length() + 1;
									if (word.find(",") < 256 || counter_idenf_in_one_line == atoi(amountParam.c_str()) ) { Idenf = "";continue; }
									else { std::cout << "error"; }
								}
							
							



							
							
							}

							

							//Поиск ) в конце параметров перед ними и после не должно быть лишнего текста

							if (line.find(pastIdenf)+pastIdenf.length()== line.find(")") || line.find(pastIdenf) + pastIdenf.length() + 1 == line.find(")"))
							{



								/*if (word.find("{") < 256) { std::cout << "fine"; }
								else { ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0); }*/

							}
							else {
								//std::cout << line.find(pastIdenf) + pastIdenf.length() << std::endl;

								ERROR_THROW_IN(117,sepline+separat(separators, sepcount, positioninline), 0);

							}
							if (line.find(";") < 256)
							{
								if (line.find(")") + 1 == line.find(";") || (line.find(")") + 2 == line.find(";") && line[line.find(")") + 1] == line.find(' ')))
								{
								}
								else
								{
									ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0);
								}
							}
							else
							{
								if (line.find(")") == line.length() - 1) {}
								else { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
							}
							sepline += sepcount;
							continue;
						}

						//поиск идентефикатора
						typeofidenf = 1;
						i = 0;
						IsItLetter = false;
						for (; i < 10; i++)
						{
							if (i == word.length()) { break; }
							for (int j = 0; j < alphabet.length(); j++) {
								if (word[i] == alphabet[j]) { IsItLetter = true; }
							}
							if (word[i] == ';') { break; }
							if (word[i] == tolower(word[i]))
							{
								if (IsItLetter == false) { ERROR_THROW_IN(119,sepline+separat(separators, sepcount, positioninline), 0); }
								Idenf += word[i];
								IsItLetter = false;
							}
							else
							{
								ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
							}

						}
						if (Idenf.length() > 5) { ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0); }//throw if letter > 5
						if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116,sepline+separat(separators, sepcount, positioninline), 0); }//throw if key word
						//конец поиска идентификатора
						counter_idenf_in_one_line += 1;
						valueofidenf = "d";
						// Запись найденного идентификатора в файл
						if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
						else {
							if (numb_of_line < 100)
							{
								idenffile << "00" << numb_of_line << "|";
							}
							else
							{
								if (numb_of_line < 1000) {
									idenffile << "0" << numb_of_line << "|";
								}
								else
								{
									if (numb_of_line < 10000) {
										idenffile << numb_of_line << "|";
									}
								}
							}
						}
						idenffile << Idenf;
						for (int j = Idenf.length(); j < 5; j++)
						{
							idenffile << " ";
						}
						idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
						if (counter_idenf_in_one_line < 10)
						{
							idenffile << "0" << counter_idenf_in_one_line;
						}
						else
						{
							idenffile << counter_idenf_in_one_line;
						}
						if (scope < 10) { idenffile << "|l_0" << scope; }
						else { idenffile << "|l_" << scope; }
						idenffile << "|" << "v_" << valueofidenf << "\n";
						// clear idenf for next idenf
					   //конец записи в файл
						valueofidenf = "";
						Idenf = "";
						if (CheckEndLine(line)) {}
						else { ERROR_THROW_IN(124, sepline + separat(separators, sepcount, positioninline), 0); }
						sepline += sepcount;
						continue;
					}
					else 
					{
						ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0);
					}

				}
				else
				{
/*main*/
///////////////////////////
					if(word == "main") 
					{
						maxscope += 1;
						scope = maxscope;
						sepline += sepcount;
						//function open
					}
					else 
					{
						//Надо ещё добавить проверку }; после ретурна,( вроде добавил, но нужны тесты)
/*return*/
//////////////////////////////
						if (word == "return") 
						{
						//functionopen = 0///////////////////////////////////////////////////

							streamLine >> word;
							positioninline += word.length() + 1;
							//поиск идентефикатора
							typeofidenf = 1;
							i = 0;
							IsItLetter = false;
							Idenf = "";
							//поиск идентефикатора
							bool isitnumber = false;
							IsItLetter = false;
							i = line.find("return");
							for (i+=7; i < 10; i++)
							{

								for (int j = 0; j < alphabet.length(); j++) {
									if (line[i] == alphabet[j]) { IsItLetter = true; }
								}
								if (line[i] == ';') { break; }
								if (line[i] == tolower(line[i]))
								{

									if (IsItLetter == false)
									{
										isitnumber = true;
										if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')
										{
											if (Idenf.length() < 2) { Idenf += line[i]; continue; }
											else {
												if (Idenf[Idenf.length() - 1] == line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')
												{
													Idenf += line[i]; continue;
												}
												else { ERROR_THROW_IN(119,sepline+separat(separators, sepcount, positioninline), 0); }
											}
										}
									}
									Idenf += line[i];
									IsItLetter = false;
								}
								else
								{
									ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
								}

							}
							positioninline += Idenf.length();
							if (Idenf.length() > 5) { ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0); }//throw if letter > 5
							if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116,sepline+separat(separators, sepcount, positioninline), 0); }//throw if key word
							//конец поиска идентификатора

							idenffile.close();
							idenffile.open(out, std::ios::in);
							std::string curLine;
							std::string numberline;
							//numb_of_line++;
							int numbline;
							int locale_view = scope;
							std::string typeoffun = "-1";
							int scopeofIdenf;
							while (getline(idenffile, curLine)) 
							{
								numberline = "";
								for (int j = 0; j < 4; j++) 
								{
									numberline += curLine[j];
								}
								numbline = atoi(numberline.c_str());//перевод номера строки в int
								numberline = "";
								if (numbline < numb_of_line) 
								{
									for (int j = curLine.find("|l_") + 3; j < curLine.find("|l_")+5; j++)//Нахождение, в какой области видимости эта функция
									{
										
										numberline += curLine[j];
									}
									scopeofIdenf = atoi(numberline.c_str()); // перевод области видимости в int


									if (curLine[curLine.find("|t_") + 3] == '2' && scopeofIdenf == scope && typeoffun == "-1") //нахождения типа функции
									{
										typeoffun = curLine[curLine.find("|d_") + 3]; // и дальше найти имя, сoвпад со scope и именем иденфа
									}
									numberline = "";
									for (int j = 5; j < 10; j++)
									{
										if (curLine[j] == ' ') { break; }
										if (curLine[j] == '|') { break; }
										numberline += curLine[j];
									}

									if (numberline == Idenf && typeoffun != "-1") {
										char data[2];
										data[0] = typeoffun[0];
										if (curLine[curLine.find("|d_") + 3] == data[0]) 
										{
											typeofdata = atoi(typeoffun.c_str());
											break;
										}
										else {
											ERROR_THROW_IN(121,sepline+separat(separators, sepcount, positioninline), 0);
										}
									}
								}
								
							}

							idenffile.close();
							idenffile.open(out, std::ios::app);


							typeofidenf = 1;
							if (isitnumber == true) { typeofidenf = 4; }
							counter_idenf_in_one_line += 1;
							// Запись найденного идентификатора в файл
							if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
							else {
								if (numb_of_line < 100)
								{
									idenffile << "00" << numb_of_line << "|";
								}
								else
								{
									if (numb_of_line < 1000) {
										idenffile << "0" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 10000) {
											idenffile << numb_of_line << "|";
										}
									}
								}
							}
							idenffile << Idenf;
							for (int j = Idenf.length(); j < 5; j++)
							{
								idenffile << " ";
							}
							idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
							if (counter_idenf_in_one_line < 10)
							{
								idenffile << "0" << counter_idenf_in_one_line;
							}
							else
							{
								idenffile << counter_idenf_in_one_line;
							}
							if (scope < 10) { idenffile << "|l_0" << scope; }
							else { idenffile << "|l_" << scope; }
							idenffile << "|" << "v_" << valueofidenf << "\n";
							// clear idenf for next idenf
						   //конец записи в файл
							Idenf = "";
							if (CheckEndLine(line)) {}
							else { ERROR_THROW_IN(124, sepline + separat(separators, sepcount, positioninline), 0); }
							sepline += sepcount;
							continue;
						}
						else 
						{
/*print*/
////////////////////
						if(word == "print"){
							
							Idenf = "";
							counter_idenf_in_one_line += 1;
							std::string numberline = "";
							if (line.find("'") < 256 && line.find("'", line.find("'") + 1) < 300) 
							{   /* set value like string 'something', but less then 255 letters */ 
								
								for (int j = line.find("'") ; j < line.find("'", line.find("'") + 1)+1; j++)
								{
									typeofdata = 2;

									if (line[j] == ';' && (j == line.length() || line.length() - 1)) { break; }
									numberline += line[j];

								}
								typeofidenf = 4;
								typeofdata = 2;
								valueofidenf = numberline;
								//counter_idenf_in_one_line += 1;
								// Запись найденного идентификатора в файл
								Idenf = "print";
								if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
								else {
									if (numb_of_line < 100)
									{
										idenffile << "00" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 1000) {
											idenffile << "0" << numb_of_line << "|";
										}
										else
										{
											if (numb_of_line < 10000) {
												idenffile << numb_of_line << "|";
											}
										}
									}
								}
								idenffile << Idenf;
								for (int j = Idenf.length(); j < 5; j++)
								{
									idenffile << " ";
								}
								idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
								if (counter_idenf_in_one_line < 10)
								{
									idenffile << "0" << counter_idenf_in_one_line;
								}
								else
								{
									idenffile << counter_idenf_in_one_line;
								}
								if (scope < 10) { idenffile << "|l_0" << scope; }
								else { idenffile << "|l_" << scope; }
								idenffile << "|" << "v_" << valueofidenf << "\n";
								// clear idenf for next idenf
							   //конец записи в файл
								typeofdata = 1;
								Idenf = "";
								valueofidenf == "";
								if (CheckEndLine(line)) {}
								else { ERROR_THROW_IN(124, sepline + separat(separators, sepcount, positioninline), 0); }
								sepline += sepcount;
								continue;

							}
							else {

								for (int j = line.find("print") + 6; j < line.length(); j++)
								{
									typeofdata = 1;
									if (line[j] == ' ') { continue; }
									if (line[j] == '=') { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
									if (line[j] == ';' && (j == line.length() || line.length() - 1)) { break; }
									numberline += line[j];

								}
							}
							valueofidenf = numberline;
							numberline = "";
							Idenf = "print";
							//Проверка idenf на то, что он сущесвует
							/////////////////////////////////
							//Отделяю функцию от скобок 






						
							//////////////////////////
							
						
							typeofidenf = 1;
							//counter_idenf_in_one_line += 1;
							// Запись найденного идентификатора в файл
							if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
							else {
								if (numb_of_line < 100)
								{
									idenffile << "00" << numb_of_line << "|";
								}
								else
								{
									if (numb_of_line < 1000) {
										idenffile << "0" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 10000) {
											idenffile << numb_of_line << "|";
										}
									}
								}
							}
							idenffile << Idenf;
							for (int j = Idenf.length(); j < 5; j++)
							{
								idenffile << " ";
							}
							idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
							if (counter_idenf_in_one_line < 10)
							{
								idenffile << "0" << counter_idenf_in_one_line;
							}
							else
							{
								idenffile << counter_idenf_in_one_line;
							}
							if (scope < 10) { idenffile << "|l_0" << scope; }
							else { idenffile << "|l_" << scope; }
							idenffile << "|" << "v_" << valueofidenf << "\n";
							// clear idenf for next idenf
						   //конец записи в файл
							Idenf = "";



							//Нужна проверка функций и существования переменных




							if (CheckEndLine(line)) {}
							else { ERROR_THROW_IN(124, sepline + separat(separators, sepcount, positioninline), 0); }
							sepline += sepcount;
							continue;
						}
						else {
							if (line.find("=") < 256)
							{
								if (line[line.find("=") + 1] == ' ')
								{
									positioninline += 1;
								}

							}
							else { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
							counter_idenf_in_one_line = 0;
							positioninline += 1;
							//поиск идентефикатора
							typeofidenf = 1;
							i = 0;
							IsItLetter = false;
							for (; i < 10; i++)
							{
								if (i == word.length()) { break; }
								for (int j = 0; j < alphabet.length(); j++) {
									if (word[i] == alphabet[j]) { IsItLetter = true; }
								}
								if (word[i] == ' ') { break; }
								if (word[i] == ';') { break; }
								if (word[i] == tolower(word[i]))
								{
									if (IsItLetter == false) { ERROR_THROW_IN(119,sepline+separat(separators, sepcount, positioninline), 0); }
									Idenf += word[i];
									IsItLetter = false;
								}
								else
								{
									ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
								}

							}
							positioninline += Idenf.length() + 1;
							if (Idenf.length() > 5) { ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0); }//throw if letter > 5
							if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116,sepline+separat(separators, sepcount, positioninline), 0); }//throw if key word
							//конец поиска идентификатора
							counter_idenf_in_one_line += 1;
							if (line[line.find(Idenf)+Idenf.length() + 1] == '=' || line[line.find(Idenf)+Idenf.length()] == '=') {}
							else { ERROR_THROW_IN(114,sepline+separat(separators, sepcount, positioninline), 0); }

							int data;


							std::string curLine;
							std::string numberline;

							int numbline;
							int locale_view = scope;
							std::string dataChangeIdenf = "-1";
							int scopeofIdenf;
							idenffile.close();
							idenffile.open(out, std::ios::in);
							while (getline(idenffile, curLine))// find idenf and it data type
							{
								numberline = "";
								for (int j = 0; j < 4; j++)
								{
									numberline += curLine[j];
								}
								numbline = atoi(numberline.c_str());//перевод номера строки в int
								numberline = "";
								if (numbline < numb_of_line)
								{
									for (int j = curLine.find("|l_") + 3; j < curLine.find("|l_") + 5; j++)//Нахождение, в какой области видимсоти должна быть переменная
									{

										numberline += curLine[j];
									}
									scopeofIdenf = atoi(numberline.c_str()); // перевод области видимости в int
									numberline = "";
									for (int j = 5; j < 10; j++)
									{
										if (curLine[j] == ' ') { break; }
										if (curLine[j] == '|') { break; }
										numberline += curLine[j];
									}


									if (curLine[curLine.find("|t_") + 3] == '1' && scopeofIdenf == scope && dataChangeIdenf == "-1" && numberline == Idenf) //нахождения типа переменной
									{
										dataChangeIdenf = curLine[curLine.find("|d_") + 3]; 
										typeofdata = atoi(dataChangeIdenf.c_str());
										break;
									}
									
								
								}

							}
							idenffile.close();
							idenffile.open(out, std::ios::app);
							if (dataChangeIdenf == "-1") { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
							numberline = "";

							//нахождение выражений/функций после равно

							//вся строка после равно
							if (line.find("'") < 256 && line.find("'", line.find("'") + 1)<300) {  
								/* set value like string 'something', but less then 255 letters */  
								if (typeofdata == 1) { ERROR_THROW_IN(125, sepline + separat(separators, sepcount, positioninline), 0); }


								for (int j = line.find("'"); j < line.find("'", line.find("'") + 1) + 1; j++)
								{
									typeofdata = 2;

									if (line[j] == ';' && (j == line.length() || line.length() - 1)) { break; }
									numberline += line[j];

								}
								typeofdata = 2;
								valueofidenf = numberline;
								numberline = "";
								//counter_idenf_in_one_line += 1;
								// Запись найденного идентификатора в файл
								if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
								else {
									if (numb_of_line < 100)
									{
										idenffile << "00" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 1000) {
											idenffile << "0" << numb_of_line << "|";
										}
										else
										{
											if (numb_of_line < 10000) {
												idenffile << numb_of_line << "|";
											}
										}
									}
								}
								idenffile << Idenf;
								for (int j = Idenf.length(); j < 5; j++)
								{
									idenffile << " ";
								}
								idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
								if (counter_idenf_in_one_line < 10)
								{
									idenffile << "0" << counter_idenf_in_one_line;
								}
								else
								{
									idenffile << counter_idenf_in_one_line;
								}
								if (scope < 10) { idenffile << "|l_0" << scope; }
								else { idenffile << "|l_" << scope; }
								idenffile << "|" << "v_" << valueofidenf << "\n";
								// clear idenf for next idenf
							   //конец записи в файл
								typeofdata = 1;
								Idenf = "";
								if (CheckEndLine(line)) {}
								else { ERROR_THROW_IN(124, sepline + separat(separators, sepcount, positioninline), 0); }
								sepline += sepcount;
								continue;

							
							
							
							}
							else { 

								for (int j = line.find("=") + 1; j < line.length(); j++)
								{
									if (line[j] == ' ') { continue; }
									if (line[j] == '=') { ERROR_THROW_IN(120,sepline+separat(separators, sepcount, positioninline), 0); }
									if (line[j] == ';' && (j == line.length() || line.length() - 1)) { break; }
									numberline += line[j];

								}
							}
								valueofidenf = numberline;
								numberline = "";							
							typeofidenf = 1;
							//counter_idenf_in_one_line += 1;
							// Запись найденного идентификатора в файл
							if (numb_of_line < 10) { idenffile << "000" << numb_of_line << "|"; }
							else {
								if (numb_of_line < 100)
								{
									idenffile << "00" << numb_of_line << "|";
								}
								else
								{
									if (numb_of_line < 1000) {
										idenffile << "0" << numb_of_line << "|";
									}
									else
									{
										if (numb_of_line < 10000) {
											idenffile << numb_of_line << "|";
										}
									}
								}
							}
							idenffile << Idenf;
							for (int j = Idenf.length(); j < 5; j++)
							{
								idenffile << " ";
							}
							idenffile << "|" << "d_" << typeofdata << "|" << "t_" << typeofidenf << "|" << "a_";
							if (counter_idenf_in_one_line < 10)
							{
								idenffile << "0" << counter_idenf_in_one_line;
							}
							else
							{
								idenffile << counter_idenf_in_one_line;
							}
							if (scope < 10) { idenffile << "|l_0" << scope; }
							else { idenffile << "|l_" << scope; }
							idenffile << "|" << "v_" << valueofidenf << "\n";
							// clear idenf for next idenf
						   //конец записи в файл
							
							

							////проверка соответствия типов литералов и типа переменной
							
							int idenfdatatype = typeofdata;
							typeofidenf = 1;
							i = 0;
							bool isitfunction = false;
							int numbfunline;
							std::string params = "";
							int paramcounter=0;
							bool isitnumber = false;
							std::string afterequal;
							int prevscope = scope;
							bool FindInFile = true;

							while (1) {
								if (FindInFile == true || Idenf == "("
									|| Idenf == ")" || Idenf == "-" || Idenf == "+"
									|| Idenf == "/" || Idenf == "*" || Idenf == "")
								{
									FindInFile = false;
								}

								else {

									ERROR_THROW_IN(120, sepline + separat(separators, sepcount, positioninline), 0);
								}
								Idenf = "";
								//поиск идентефикатора
								IsItLetter = false;
								for (; i < valueofidenf.length(); i++)
								{

									for (int j = 0; j < alphabet.length(); j++) {
										if (valueofidenf[i] == alphabet[j]) { IsItLetter = true; }
									}

									if (valueofidenf[i] == ')') { i++; break; }
									if (valueofidenf[i] == '(') { i++; break; }
									if (valueofidenf[i] == '-') { i++; break; }
									if (valueofidenf[i] == '+') { i++; break; }
									if (valueofidenf[i] == '/') { i++; break; }
									if (valueofidenf[i] == '*') { i++; break; }
									if (isitfunction == true) { if (valueofidenf[i] == ',') { i++; break; } }
									if (valueofidenf[i] == tolower(valueofidenf[i]))
									{

										if (IsItLetter == false)
										{
											isitnumber = true;
											if (valueofidenf[i] == '0' || valueofidenf[i] == '1' || valueofidenf[i] == '2' || valueofidenf[i] == '3' || valueofidenf[i] == '4' || valueofidenf[i] == '5' || valueofidenf[i] == '6' || valueofidenf[i] == '7' || valueofidenf[i] == '8' || valueofidenf[i] == '9')
											{
												if (Idenf.length() < 2) { Idenf += valueofidenf[i]; continue; }
												else {
													if (Idenf[Idenf.length() - 1] == valueofidenf[i] == '0' || valueofidenf[i] == '1' || valueofidenf[i] == '2' || valueofidenf[i] == '3' || valueofidenf[i] == '4' || valueofidenf[i] == '5' || valueofidenf[i] == '6' || valueofidenf[i] == '7' || valueofidenf[i] == '8' || valueofidenf[i] == '9')
													{
														Idenf += valueofidenf[i]; continue;
													}
													else { ERROR_THROW_IN(119, sepline + separat(separators, sepcount, positioninline), 0); }
												}
											}
										}
										Idenf += valueofidenf[i];
										IsItLetter = false;
									}

									else
									{
										ERROR_THROW_IN(114, sepline + separat(separators, sepcount, positioninline), 0);//throw error of big letter in idenf 
									}

								}
								positioninline += Idenf.length() + 1;

								if (Idenf == "integer" || Idenf == "declare" || Idenf == "print" || Idenf == "main") { ERROR_THROW_IN(116, sepline + separat(separators, sepcount, positioninline), 0); }//throw if key word
								//конец поиска идентификатора



								//поиск соответствия типа и запись в отдельную переменную, а потом и в файл, после Idenf = ""

								idenffile.close();
								idenffile.open(out, std::ios::in);
								bool somethingFind = false;
								while (getline(idenffile, curLine))// find idenf and it data type
								{
									numberline = "";
									for (int j = 0; j < 4; j++)
									{
										numberline += curLine[j];
									}
									numbline = atoi(numberline.c_str());//перевод номера строки в int
									numberline = "";
									if (numbline < numb_of_line) // построчная проверка файла с идентификаторами
									{
										for (int j = curLine.find("|l_") + 3; j < curLine.find("|l_") + 5; j++)//Нахождение, в какой области видимсоти должна быть переменная
										{

											numberline += curLine[j];
										}
										if (isitnumber == false) { prevscope = atoi(numberline.c_str()); }
										scopeofIdenf = atoi(numberline.c_str()); // перевод области видимости в int
										numberline = "";
										if (isitnumber == true) { scopeofIdenf = prevscope; }
										for (int j = 5; j < 15; j++)//взять Idenf из файла
										{
											if (curLine[j] == ' ') { break; }
											if (curLine[j] == '|') { break; }
											numberline += curLine[j];
										}


										if (scopeofIdenf == scope && numberline == Idenf || isitnumber == true || numberline == Idenf && curLine[curLine.find("|v_") + 3] == 'f') //нахождения типа переменной
										{
											somethingFind = true;
											FindInFile = true;
											std::string type;
											std::string value = "";
											dataChangeIdenf = curLine[curLine.find("|d_") + 3];
											type = curLine[curLine.find("|t_") + 3];
											if (isitnumber == true) { dataChangeIdenf = "1"; type = "4"; }
											if (atoi(dataChangeIdenf.c_str()) == idenfdatatype && isitfunction == false && isitnumber == false) {
												FindInFile = true;
												//При успешном совпадении типов занесение в отдельную переменную, а потом в сам файл
												typeofidenf = 1;
												if (isitnumber == true) { typeofidenf = 4; typeofdata = 1; }
												//если это функция
												if (atoi(type.c_str()) == 2)
												{
													type = ""; // use next as a data types if params
													typeofidenf = 2; value = "v"; isitfunction = true;
													numbfunline = numbline;
													while (getline(idenffile, curLine)) //find all params in function
													{
														numberline = "";
														for (int j = 0; j < 4; j++)
														{
															numberline += curLine[j];
														}
														numbline = atoi(numberline.c_str());//перевод номера строки в int
														numberline = "";

														if (numbline == numbfunline)
														{

															params += curLine[curLine.find("|d_") + 3];

														}
														else
														{
															break;
														}


													}


												}
												counter_idenf_in_one_line += 1;
												// Запись найденного идентификатора в файл
												if (numb_of_line < 10) { afterequal += "000"; afterequal += std::to_string(numb_of_line); afterequal += "|"; }
												else {
													if (numb_of_line < 100)
													{
														afterequal += "00"; afterequal += std::to_string(numb_of_line); afterequal += "|";
													}
													else
													{
														if (numb_of_line < 1000) {
															afterequal += "0"; afterequal += std::to_string(numb_of_line); afterequal += "|";
														}
														else
														{
															if (numb_of_line < 10000) {
																afterequal += std::to_string(numb_of_line); afterequal += "|";
															}
														}
													}
												}
												afterequal += Idenf;
												for (int j = Idenf.length(); j < 5; j++)
												{
													afterequal += " ";
												}
												afterequal += "|"; afterequal += "d_"; afterequal += std::to_string(typeofdata); afterequal += "|"; afterequal += "t_"; afterequal += std::to_string(typeofidenf); afterequal += "|a_";
												if (counter_idenf_in_one_line < 10)
												{
													afterequal += "0"; afterequal += std::to_string(counter_idenf_in_one_line);
												}
												else
												{
													afterequal += std::to_string(counter_idenf_in_one_line);
												}
												if (scope < 10) { afterequal += "|l_0"; afterequal += std::to_string(scope); }
												else { afterequal += "|l_"; afterequal += std::to_string(scope); }
												afterequal += "|v_"; afterequal += value; afterequal += "\n";
												// clear idenf for next idenf
											   //конец записи в файл
												value = "";
												break;
											}
											else
											{
												if (isitfunction == true)
												{
													FindInFile = true;
													typeofidenf = 3;
													typeofdata = atoi(dataChangeIdenf.c_str());
													paramcounter += 1;

													if (paramcounter == params.length())
													{
														if (line.find(Idenf + ")", i) < 256 || line.find(Idenf + " )", i) < 256) { isitfunction = false; }
														else
														{
															ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
														}

													}
													if (paramcounter < params.length())
													{
														if (line.find(Idenf + ")", i) < 256 || line.find(Idenf + " )", i) < 256) { ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0); }

													}
													//if (paramcounter == params.length()) { isitfunction = false; }
													if (isitnumber == true) { dataChangeIdenf = "1"; isitnumber = false; }
													if (dataChangeIdenf[0] == params[paramcounter - 1])
													{

														counter_idenf_in_one_line += 1;
														// Запись найденного идентификатора в файл
														if (numb_of_line < 10) { afterequal += "000"; afterequal += std::to_string(numb_of_line); afterequal += "|"; }
														else {
															if (numb_of_line < 100)
															{
																afterequal += "00"; afterequal += std::to_string(numb_of_line); afterequal += "|";
															}
															else
															{
																if (numb_of_line < 1000) {
																	afterequal += "0"; afterequal += std::to_string(numb_of_line); afterequal += "|";
																}
																else
																{
																	if (numb_of_line < 10000) {
																		afterequal += std::to_string(numb_of_line); afterequal += "|";
																	}
																}
															}
														}
														afterequal += Idenf;
														for (int j = Idenf.length(); j < 5; j++)
														{
															afterequal += " ";
														}
														afterequal += "|"; afterequal += "d_"; afterequal += std::to_string(typeofdata); afterequal += "|"; afterequal += "t_"; afterequal += std::to_string(typeofidenf); afterequal += "|a_";
														if (counter_idenf_in_one_line < 10)
														{
															afterequal += "0"; afterequal += std::to_string(counter_idenf_in_one_line);
														}
														else
														{
															afterequal += std::to_string(counter_idenf_in_one_line);
														}
														if (scope < 10) { afterequal += "|l_0"; afterequal += std::to_string(scope); }
														else { afterequal += "|l_"; afterequal += std::to_string(scope); }
														afterequal += "|v_"; afterequal += value; afterequal += "\n";
														// clear idenf for next idenf
													   //конец записи в файл
														break;
													}
													else
													{
														ERROR_THROW_IN(117, sepline + separat(separators, sepcount, positioninline), 0);
														//put error
													}



												}
												else
												{
													if (isitnumber == true)
													{
														FindInFile = true;
														isitnumber = false;
														typeofdata = 1;
														typeofidenf = 4;
														counter_idenf_in_one_line += 1;
														// Запись найденного идентификатора в файл
														if (numb_of_line < 10) { afterequal += "000"; afterequal += std::to_string(numb_of_line); afterequal += "|"; }
														else {
															if (numb_of_line < 100)
															{
																afterequal += "00"; afterequal += std::to_string(numb_of_line); afterequal += "|";
															}
															else
															{
																if (numb_of_line < 1000) {
																	afterequal += "0"; afterequal += std::to_string(numb_of_line); afterequal += "|";
																}
																else
																{
																	if (numb_of_line < 10000) {
																		afterequal += std::to_string(numb_of_line); afterequal += "|";
																	}
																}
															}
														}
														afterequal += Idenf;
														for (int j = Idenf.length(); j < 5; j++)
														{
															afterequal += " ";
														}
														afterequal += "|"; afterequal += "d_"; afterequal += std::to_string(typeofdata); afterequal += "|"; afterequal += "t_"; afterequal += std::to_string(typeofidenf); afterequal += "|a_";
														if (counter_idenf_in_one_line < 10)
														{
															afterequal += "0"; afterequal += std::to_string(counter_idenf_in_one_line);
														}
														else
														{
															afterequal += std::to_string(counter_idenf_in_one_line);
														}
														if (scope < 10) { afterequal += "|l_0"; afterequal += std::to_string(scope); }
														else { afterequal += "|l_"; afterequal += std::to_string(scope); }
														afterequal += "|v_"; afterequal += value; afterequal += "\n";
														// clear idenf for next idenf
													   //конец записи в файл
														Idenf == "";
														break;
													}
													else
													{
														ERROR_THROW_IN(123, sepline + separat(separators, sepcount, positioninline), 0);
													}

												}

											}

										}

									}
								}

								if (somethingFind == false && counter_idenf_in_one_line == 1)
								{

									ERROR_THROW_IN(125, sepline + separat(separators, sepcount, positioninline)+1, 0);
								}
								idenffile.close();
								idenffile.open(out, std::ios::app);
								idenffile << afterequal;
								afterequal = "";
								//

								
							//	counter_idenf_in_one_line += 1;
								if (i == valueofidenf.length()) { break; }
							}
							valueofidenf = "";

							if (CheckEndLine(line)) {}
							else { ERROR_THROW_IN(124, sepline + separat(separators, sepcount, positioninline), 0); }
							sepline += sepcount;
							continue;
						}


						}
					}
				}
			}

		}
		idenffile.close();
	}


	int separat(int Arr[], int sepcount, int linepos) 
	{
		int sep = 0;
		for (int i = sepcount - 1; i > -1; i--) 
		{
			
			if (linepos > Arr[i]) 
			{
					sep = i;
					return sep;
			}
			
		}
		return 1;
	}


	bool CheckEndLine(std::string line) 
	{
		
		if (line.find(";") == line.length() || line.find(";") == line.length() - 1 || line.find(";") == line.length() - 2)
		{
		return true;
		}
		else 
		{
			return false;
		}
	}




	//Таблица лексем без конечного автомата
	IN readfile (wchar_t infile[], int kostil, wchar_t outfile[])
	{
		setlocale(LC_CTYPE, "rus");
		IN inn;
		inn.size = 0;
		inn.lines = 1;
		inn.ignor = 0;
		int start = 0, finish = 0;
		char text1[1000] = {}; char abc[1000] = {}; int cabc = 0;
		unsigned short position = 0;


		std::fstream input; input.open(infile, std::ios::in);
		if (!input) { throw ERROR_THROW(110) }
		char letter[1];
		Log::LOG log;
		log.stream = new std::ofstream;
		log.stream->open(outfile);
		if (!log.stream->is_open()) { throw ERROR_THROW(112); }
		wcscpy_s(log.logfile, outfile);
		char analtable[] = "|integer_t|string_t|function_f|declare_d|return_r|print_p|main_m|;_;|,_,|{_{|}_}|(_(|)_)|+_v|-_v|=_=|*_v|/_v|";
		// put first number of line
		    *log.stream << "0";
			*log.stream << inn.lines;
			*log.stream << " ";
		// 
		bool finefind = false;
		bool findsameletter = false;
		int firstenter = 0;
		char prevlecsem[2];
		bool afterfunction = true;
		bool putidenf = false;
		bool findfirstbrackets = false;
		bool findsecondbrackets = false;
		char bracket[2] = "'";
		int posOneletterIdenf = 0;
		while (!input.eof())
		{
			char ch = input.get();
			if (inn.code[(int)ch + 256] == IN::I)
			{
				goto ifFindEndOfFile;
			} //Убирает символ конца файла 
			letter[0] = ch;




			if (ch == bracket[0] && (findfirstbrackets == false || findsecondbrackets == false)) //Ищет строки
			{
				if (findfirstbrackets == true) 
				{ 
					std::cout << "l";
					*log.stream << "l";
					findsecondbrackets = false;
					findfirstbrackets = false;
					continue;
				}
				findfirstbrackets = true;

			}
			if (findfirstbrackets == true) {
				if (findfirstbrackets == true && findsecondbrackets == true)
				{
					findfirstbrackets = false;
					findfirstbrackets = false;
				}
				continue;
			}
			

			//если нашло функцию
			if (prevlecsem[0] == 'f')
			{

				std::cout << 'i';

				prevlecsem[0] = 'i';
				*log.stream << 'i';
				ch = input.get();
				while (1)
				{
					if (ch == '(') 
					{
						std::cout << '(';
						*log.stream << '(';
						break;
					}
					prevlecsem[1] = '(';
					ch = input.get();
					afterfunction = true;
				}
				

				finefind = false;
				findsameletter = false;
				putidenf == false;

			}

			// скобки в функции
			if (prevlecsem[0] == 't' && prevlecsem[1] == '(' && afterfunction==true)
			{
				bool functionclose=false;
				std::cout << "i";
				*log.stream << 'i';

				while (1)
				{
					ch = input.get();
					
					if (ch == ',') 
					{
						std::cout << "," << "t" << "i";
						*log.stream << ",";
						*log.stream << "t";
						*log.stream << "i";
					}
					if (ch == ')') 
					{
						std::cout << ")";
						*log.stream << ")";
						ch = input.get();
						letter[0] = ch;
						break;
					}
				}


				prevlecsem[0] = ')';
				prevlecsem[1] = NULL;
				findsameletter = false;
				afterfunction = false;
				finefind = false;
				putidenf == false;
			}


			//    новая строка \n
			if (letter[0] == '\n') {
				inn.lines += 1;
				*log.stream << "\n";
				std::cout << "\n";
				// put number of line
				if (inn.lines < 10)
				{
					*log.stream << "0"; *log.stream << inn.lines; *log.stream << " ";
				}
				else {
					*log.stream << inn.lines;
					*log.stream << " ";
				}
				findsameletter == false;
				continue;
			}



			if (findsameletter == true) {
				firstenter += 1;
				posOneletterIdenf += 1;
				if (letter[0] == analtable[firstenter]) {
					finefind = true;
				}
				else {
					finefind = false;
					findsameletter = false;
					if ((prevlecsem[0] == '=' || posOneletterIdenf == 2) && putidenf==false)
					{
						std::cout << "i";
						*log.stream << "i";
						putidenf = true;
					}
				}
				if (finefind = true && analtable[firstenter + 1] == '_') {
					std::cout << analtable[firstenter + 2];
					if (prevlecsem[0] == 'd' && analtable[firstenter+2]== 't') 
					{
						prevlecsem[1] = 'd';
					}
					putidenf == false;
					prevlecsem[0] = analtable[firstenter + 2];
					*log.stream << analtable[firstenter + 2];
				}
			}

			if (findsameletter == false) 
			{
				for (int i = 0; i < strlen(analtable),findsameletter==false; i++) 
				{
					if (letter[0] == ' ') { break; }
					if (i > 108) 
					{ 
						

						if ((letter[0] == '0' || letter[0] == '1' || letter[0] == '2' || letter[0] == '3' || letter[0] == '4' || letter[0] == '5' || letter[0] == '6' || letter[0] == '7' || letter[0] == '8' || letter[0] == '9') && putidenf==false) 
						{
							std::cout << "l";
							*log.stream << "l";
							putidenf = true;
						}
						if (putidenf == false)
						{
							std::cout << "i";
							*log.stream << "i";
							putidenf = true;
						}
						
						break;
					
					}
					if (letter[0]==analtable[i] && analtable[i-1] == '|') 
					
					{ 
						if (analtable[i + 1] == '_') 
						{
							prevlecsem[0] = analtable[i + 2];
							putidenf = false;
							std::cout << analtable[i + 2];
							*log.stream << analtable[i + 2]; 
							break;
						}
						else {
							posOneletterIdenf = 1;
							firstenter = i;
							findsameletter = true;
							finefind = true;
							break;
						}
					}
				}
			}


			if ((int)ch >= 0)
			{
				if (inn.code[(int)ch] == IN::T)
				{
					++inn.size;
					if ((ch == '\n') || (ch == '\0')) {
						++inn.lines;
					}
					text1[position] = ch;
					++position;
				}
			}
			else if ((int)ch < 0)
			{
				if (inn.code[(int)ch + 256] == IN::T)
				{
					++inn.size;
					if ((ch == '\n') || (ch == '\0'))
						++inn.lines;		*log.stream << inn.lines;
					text1[position] = ch;
					++position;
				}
			}

			inn.text = &text1[0];
		}
	ifFindEndOfFile:
		*log.stream << letter[0];
		log.stream->close();

		return inn;
	}
}
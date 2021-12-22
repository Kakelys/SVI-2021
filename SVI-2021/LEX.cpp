#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include "Log.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "LEX.h"
#include "LT.h"
#pragma warning(disable : 6262)


namespace LEX
{





	void lexTable(wchar_t outfile[], IT::IdTable& idenfs, LT::LexTable& lexems)
	{


		std::fstream input; input.open("il.txt", std::ios::in);
		if (!input) { throw ERROR_THROW(113) }
		std::string line;
		std::string word;
		std::string fun = "";
		std::string prevfun = "";
		word = "";
		int i = 0; // counter for line
		bool somethingelse = false;
		int linecounter = 0;
		int InfinityCycle = 0;
		int datatype = 0, equaldatatype = 0;;
		int type = 0;
		bool isfunction = false, isdeclare = false, function = false, isif = false;
		int lexemcounter = 0, idenfscounter = 0, litcounter = 0;;
		int sepline = 0;
		int scope = 0, subscope = 0, maxscope = 0;
		bool isequal = false;
		int ParmCount = 0;

		while (std::getline(input, line))
		{

			//Создание массива позиций сепараторов и их дальнешее удаление из строки
			std::string nosep;
			int sepcount = 0;
			for (int j = 0; j < line.length(); j++)
			{
				if (line[j] == (char)0x95)
				{
					sepcount++;
				}
			}
			int* separators = new int[sepcount];
			for (int j = 0, k = 0; j < line.length(); j++)
			{
				if (line[j] == (char)0x95)
				{
					separators[k] = j + 1;
					k++;
				}
				else { nosep += line[j]; }
			}
			line = nosep;
			//nosep для того, что replace оставляет пустые места										   
																										   
			linecounter++;																				   
																										   
			i = 0;																						   
			while (i != line.length())																	   
			{																							   
				word = "";																				   
				//отделением лексемы от строки															   
				for (; i < line.length(); i++)
				{
					if (line[i] == ',' || line[i] == '(' || line[i] == ')' || \
						line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == ';' ||\
						line[i] == '>' || line[i] == '<' || line[i] == '!' || (line[i] == '='))
					{
						if (somethingelse == true)
						{
							//Костыль для минусовых чисел
							if (line[i] == '-' && ((line[i-1] == '=' || line[i-2] == '=') || (line[i - 1] == '(' || line[i - 2] == '(') || (line[i - 1] == '>' || line[i - 2] == '>') || (line[i - 1] == '<' || line[i - 2] == '<') || (line[i - 1] == 't' || line[i - 2] == 't')))
							{
								word += line[i];
								somethingelse = false;
								continue;
								
							}
							word += line[i];
							somethingelse = false;
							//Небольшой костыль для сравнений 
							if (line[i + 1] == '=' && line[i]!= ')')
							{
								word += "="; i++; 
							}
							
								i++;
							
							break;
						}
						somethingelse = true;
						break;
					}
					if (line[i] == ' ') { i++; break; }
					//Что-то с отделением строки
					if (line[i] == 0x22)
					{
						for (int j = line.find(0x22, i + 1); i < j + 1; i++)
						{

							word += line[i];
						}
						//word += 0x27;
						//i++;
						//std::cout << word;
						break;
					}
					word += line[i];
				}
				char* words = new char[word.length() + 1];
				strcpy(words, word.c_str());
				InfinityCycle += 1;


				for (int j = 0; j < 1; j++) {
					//integer 
					FST::FST integer(words, fst_integer); if (FST::execute(integer))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_INTEGER;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);



						datatype = 1;
						InfinityCycle = 0;
						break;

					}
					//string  
					FST::FST strg(words, fst_string); if (FST::execute(strg))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_STRING;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);




						datatype = 2;
						InfinityCycle = 0;
						break;
					}
					//function 
					FST::FST func(words, fst_function); if (FST::execute(func))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_FUNCTION;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);

						scope = maxscope + 1; maxscope++;


						type = 2;
						isfunction = true;
						function = true;
						InfinityCycle = 0;
						break;
					}
					//declare 
					/*FST::FST declare(words, fst_declare); if (FST::execute(declare))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_DECLARE;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);



						isdeclare = true;
						type = 1;
						InfinityCycle = 0; break;
					}*/
					//if
					FST::FST condition(words, fst_if); if (FST::execute(condition))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_IF;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);


						isif = true;
						InfinityCycle = 0;
						break;
					}
					//if_op
					FST::FST condition_op(words, fst_if_op); if (FST::execute(condition_op)) 
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_IF_OP;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						lexem.condition = word;
						LT::Add(lexems, lexem);
					
					
					
						InfinityCycle = 0;
						break;
					}
					//else
					FST::FST eLse(words, fst_else); if (FST::execute(eLse))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_ELSE;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						lexem.condition = word;
						LT::Add(lexems, lexem);


						isif=true;
						InfinityCycle = 0;
						break;
					}


					//return 
					FST::FST retrn(words, fst_return); if (FST::execute(retrn))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_RETURN;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);




						type = 1;
						InfinityCycle = 0;
						break;
					}
					//print 
					FST::FST prnt(words, fst_print); if (FST::execute(prnt))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_PRINT;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);




						InfinityCycle = 0;
						break;

					}
					//main 
					FST::FST mmain(words, fst_main); if (FST::execute(mmain))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_MAIN;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						scope = maxscope + 1; maxscope++;
						subscope = 0;
						isfunction = true;
						fun = "m";


						InfinityCycle = 0;
						break;
					}
					//arifm 
					FST::FST arifm(words, fst_arifm); if (FST::execute(arifm))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = word;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);





						InfinityCycle = 0;
						break;
					}
					//int literal 8
					FST::FST integerliteral_8(words, fst_integer_lit_8); if (FST::execute(integerliteral_8))
					{
						lexemcounter++;
						idenfscounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LITERAL;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = idenfscounter - 1;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						//Проверка типов, но зачем она тут была, уже не помню
					/*	if (lexems.table[lexemcounter - 1].lexema == "=")
						{
							if (idenfs.table[idenfscounter - 2].datatype == 1)
							{
								idenfs.table[idenfscounter - 1].value.vint = atoi(word.c_str());
							}
							else { ERROR_THROW_IN(123, sepline + separat(separators, sepcount, i), 0); }
						}*/


						litcounter++;
						IT::Entry idenf;
						idenf.name = "lit" + std::to_string(litcounter);
						idenf.scope = scope;
						idenf.subscope = subscope;
						idenf.type = 4;
						idenf.datatype = 1;
						idenf.indexfirstLE = sepline + separat(separators, sepcount, i);

						if (idenfscounter > 1) {
							if (idenfscounter > 1 && IT::IsId(idenfs, word, scope, subscope) < IT_NULLIDX)
							{
								idenf.indexfirstLE = IT::IsId(idenfs, word, scope, subscope);
							}
							else
							{
								idenf.indexfirstLE = sepline + separat(separators, sepcount, i);
							}
						}
						//Перевод из 8 в 10
						long long l, N;
						bool p;
						
						if (word[0] == '-')
						{
							word.erase(0, 1);
							p = true;
						}
						else
						{
							p = false;
						}
						l = word.length();
						N = 0;
						for (int i = 0; i < l; i++)
						{
							N += (word[i] - '0') * pow(8, l - i - 1);
						}
						if (p) 
						{
							N *= -1;
						}

						//

						//std::cout << "Из числа " << word << "  в число " << N;


						idenf.value.vint = N;
						IT::Add(idenfs, idenf);





						InfinityCycle = 0;
						break;

					}
					//int literal 2 
					FST::FST integerliteral_2(words, fst_integer_lit_2); if (FST::execute(integerliteral_2))
					{
						lexemcounter++;
						idenfscounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LITERAL;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = idenfscounter - 1;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						//Проверка типов, но тут уже не нужна, на всякий оставил, если сломается без неё
						/*if (lexems.table[lexemcounter - 1].lexema == "=")
						{
							if (idenfs.table[idenfscounter - 2].datatype == 1)
							{
								idenfs.table[idenfscounter - 1].value.vint = atoi(word.c_str());
							}
							else { ERROR_THROW_IN(123, sepline + separat(separators, sepcount, i), 0); }
						}*/


						litcounter++;
						IT::Entry idenf;
						idenf.name = "lit" + std::to_string(litcounter);
						idenf.scope = scope;
						idenf.subscope = subscope;
						idenf.type = 4;
						idenf.datatype = 1;

						if (idenfscounter > 1) {
							if (idenfscounter > 1 && IT::IsId(idenfs, word, scope, subscope) < IT_NULLIDX)
							{
								idenf.indexfirstLE = IT::IsId(idenfs, word, scope, subscope);
							}
							else
							{
								idenf.indexfirstLE = sepline + separat(separators, sepcount, i);
							}
						}

						int N = 0;
						std::string value = word.substr(2,word.length()-2);
						for (int i = 0; i < value.length(); i++)
						{
							N *= 2;
							N += value[i] - '0';
						}
						switch (word[0]) 
						{
						case '1': N = -N;
							break;
						case '0': break;
						}


						idenf.value.vint = N;
						IT::Add(idenfs, idenf);





						InfinityCycle = 0;
						break;

					}




					//string literal 
					FST::FST strngliteral(words, fst_string_literal); if (FST::execute(strngliteral))
					{
						lexemcounter++;
						idenfscounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LITERAL;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = idenfscounter - 1;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						//Проверка
						/*if (lexems.table[lexemcounter - 2].lexema == "=")
						{
							if (idenfs.table[idenfscounter - 2].datatype == 2)
							{
								word = word.substr(1, word.length() - 2);


								strcpy(idenfs.table[idenfscounter - 1].value.vstr->str, word.c_str());
								idenfs.table[idenfscounter - 1].value.vstr->len = word.length();
							}
							else { ERROR_THROW_IN(123, sepline + separat(separators, sepcount, i), 0); }
						}*/

						IT::Entry idenf;
						litcounter++;
						idenf.name = "lit" + std::to_string(litcounter);
						idenf.scope = scope;
						idenf.subscope = subscope;
						idenf.type = 4;
						idenf.datatype = 2;
						if (idenfscounter > 1) {
							if (idenfscounter > 1 && IT::IsId(idenfs, word, scope, subscope) < IT_NULLIDX)
							{
								idenf.indexfirstLE = IT::IsId(idenfs, word, scope, subscope);
							}
							else
							{
								idenf.indexfirstLE = sepline + separat(separators, sepcount, i);
							}
						}

						//word = word.substr(0, word.length());
						std::string temp= "";
						for (int l = 0; l < word.length(); l++) 
						{
							if (word[l] == 0x22) {  continue; }
							temp += word[l];
						}
						word = temp;



						//Максимальное кол-во символов в строке
						if (word.length() > 255) { ERROR_THROW_IN(204, sepline + separat(separators, sepcount, i), 0); }
						strcpy(idenf.value.vstr->str, word.c_str());
						idenf.value.vstr->len = word.length();
						IT::Add(idenfs, idenf);






						InfinityCycle = 0;
						break;
					}
					// )
					FST::FST rightbrace(words, fst_right_bracket); if (FST::execute(rightbrace))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_RIGHTHESIS;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						if (isfunction == true && function == false)
						{
							idenfs.table[idenfscounter - 1 - ParmCount].ParmCount = ParmCount;

							ParmCount = 0;
						}
					

						
						isfunction = false;
						if (subscope > 0 && isif !=true)
						{
							subscope--;
							isdeclare = false;
							fun = prevfun;
						}
						type = 1;

						InfinityCycle = 0;
						break;
					}
					// (
					FST::FST leftbrace(words, fst_left_bracket);  if (FST::execute(leftbrace))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LEFTHESIS;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);

						lexem = LT::GetEntry(lexems, lexemcounter - 1);
						if (lexem.lexema == LEX_ID)
						{
							isfunction = true;
							idenfs.table[idenfscounter - 1].type = 2;
						}


						InfinityCycle = 0;
						break;
					}
					// } 
					FST::FST rightcurlybrace(words, fst_curly_right_bracket); if (FST::execute(rightcurlybrace))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_RIGHTBRACE;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						if (subscope != 0 && isif !=true)
						{
							fun = prevfun;
						}
						else
						{
							prevfun = fun;
							//fun = "";
						}
						if (subscope == 0 && isif!=true) { scope = 0; }
						else { subscope--; if (subscope < 0)subscope = 0; }
						isif = false;
						InfinityCycle = 0;
						break;
					}
					// { 
					FST::FST leftcurlybrace(words, fst_curly_left_bracket); if (FST::execute(leftcurlybrace))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LEFTBRACE;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);




						isfunction = false;
						type = 1;
						InfinityCycle = 0;
						break;
					}

					// comma ,
					FST::FST comma(words, fst_comma); if (FST::execute(comma))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_COMMA;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);






						InfinityCycle = 0;
						break;
					}
					//      ; 
					FST::FST commadot(words, fst_comma_dot); if (FST::execute(commadot))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_SEMICOLON;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						



						isequal = false;
						InfinityCycle = 0;
						break;
					}
					// equal
					FST::FST equal(words, fst_equal); if (FST::execute(equal))
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_EQUAL;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);



						equaldatatype = idenfs.table[idenfscounter - 1].datatype;
						isequal = true;
						InfinityCycle = 0;
						break;
					}
					//idenf
					FST::FST fstidenf(words, fst_idenf); if (FST::execute(fstidenf))
					{
						idenfscounter++;
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_ID;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = idenfscounter - 1;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						if (word.length() > 15) { word = word.substr(0, 15); }

						if (isfunction == true && function == false)
						{
							type = 3;
							ParmCount++;

						}
						//key words check
						if (word == "printstr" || word == "printnumb")
						{
							ERROR_THROW_IN(207, sepline + separat(separators, sepcount, i), 0);
						}
						//Дописывание функции спереди идентефикатора
						if (type == 2 && lexems.table[lexemcounter - 2].lexema == LEX_FUNCTION)
						{
							if (fun == "") { prevfun = fun; }
							fun = word;
							if (subscope != 0) { word = prevfun + word; }
						}
						else
						{
							if (IT::IsFun(idenfs, idenfscounter, word)) { type = 2; }
							if (type != 2) {
								word = fun + word;
							}

						}
						//if (subscope != 0) { word = prevfun + word; }


						if (word == "printnumb" || word == "printstr" || word == "concats")
						{
							ERROR_THROW_IN(207, sepline + separat(separators, sepcount, i), 0);
						}

						function = false;
						
						//check for big letter
						for (int j = 0; j < word.length(); j++)
						{
							if (word[j] != tolower(word[j])) { ERROR_THROW_IN(205, sepline + separat(separators, sepcount, i), 0); }
						}

						


						IT::Entry idenf;
						idenf.name = word;
						idenf.scope = scope;
						idenf.subscope = subscope;
						idenf.type = type;

						if (IT::AlredyExist(idenfs, idenfscounter, word))
						{
							idenf.datatype = IT::TakeDataType(idenfs, word);
						}
						else
						{
							idenf.datatype = datatype;
						}


						if (idenfscounter >= 1) {

							if (idenfscounter > 1 && IT::IsId(idenfs, word, scope, subscope) < IT_NULLIDX)
							{
								idenf.indexfirstLE = IT::IsId(idenfs, word, scope, subscope);
							}
							else
							{
								idenf.indexfirstLE = sepline + separat(separators, sepcount, i);
							}
						}
						else
						{
							idenf.indexfirstLE = sepline + separat(separators, sepcount, i);
						}
						switch (idenf.datatype)
						{
						case 1:
							idenf.value.vint = IT_INT_DEFAULT;
							break;

						case 2:
							idenf.value.vstr->str[0] = IT_STR_DEFAULT;
							idenf.value.vstr->len = word.length();
							break;
						}


						IT::Add(idenfs, idenf);
						isdeclare = false;
						InfinityCycle = 0;
						break;

					}

				}
				if (InfinityCycle > 5) { ERROR_THROW_IN(206, sepline + separat(separators, sepcount, i), 0); }


				delete[] words;

			}
			sepline += sepcount;
		}

	}

	int separat(int Arr[], int sepcount, int linepos)
	{
		int sep = 0;
		for (int i = sepcount - 1; i > -1; i--)
		{

			if (linepos > Arr[i])
			{
				sep = sepcount - i;
				return sep;
			}

		}
		return 1;
	}

	void DisplayLT(LT::LexTable lexems)
	{
		int curLine = 1;
		LT::Entry lexem;
		for (int i = 1; i < lexems.size + 1; i++)
		{

			lexem = LT::GetEntry(lexems, i);
			if (lexem.linenumber > curLine) { std::cout << "\n"; curLine = lexem.linenumber; }
			std::cout << lexem.lexema;
		}

	}

	void DisplayLtOneByOne(LT::LexTable lexems) 
	{
		int curLine = 1;
		LT::Entry lexem;
		for (int i = 1; i < lexems.size + 1; i++)
		{

			lexem = LT::GetEntry(lexems, i);
			
			std::cout << "|" << lexem.lexema << "| line -" << lexem.linenumber << "| index Ti - " << lexem.indexTI << "|\n";
		}
	}

	void DisplayIT(IT::IdTable idenfs)
	{
		IT::Entry idenf;
		for (int i = 1; i < idenfs.size + 1; i++)
		{
			idenf = IT::GetEntry(idenfs, i);

			std::cout
				<< "  name - " << idenf.name
				<< "  type - " << idenf.type
				<< "  datatype - " << idenf.datatype
				<< " ParmCount - " << idenf.ParmCount
				<< " value - ";

			switch (idenf.datatype)
			{
			case 1:
				std::cout << idenf.value.vint;
				break;


			case 2:
				for (int j = 0; j < idenf.value.vstr->len && (int)idenf.value.vstr->str[j] != -52; j++)
				{
					std::cout << idenf.value.vstr->str[j];
				}
				break;
			}

			std::cout << "\n";
			
		}
	}


}


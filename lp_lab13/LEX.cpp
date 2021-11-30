#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include "Log.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "LEX.h"
#pragma warning(disable : 6262)


namespace LEX
{

	//таблица лексем через конченый автомат
	void lextable(wchar_t outfile[])
	{


		std::fstream input; input.open("il.txt", std::ios::in);
		if (!input) { throw ERROR_THROW(113) }
		std::string line;
		std::string word;
		std::fstream LexTable;
		LexTable.open(outfile, std::ios::out);
		word = "";
		int i = 0; // counter for line
		bool somethingelse = false;
		int linecounter = 0;
		int InfinityCycle = 0;
		
		while (std::getline(input, line))
		{

			std::replace(line.begin(), line.end(), (char)0x95, (char)0x00);
			linecounter++;
			if (linecounter < 10)
			{
				LexTable << "00" << linecounter << " ";
			}
			else if (linecounter < 100)
			{
				LexTable << "0" << linecounter << " ";
			}
			else if (linecounter < 1000)
			{
				LexTable << linecounter << " ";
			}
			i = 0;
			while (i != line.length())
			{
				word = "";
				for (; i < line.length(); i++)
				{
					if (line[i] == ',' || line[i] == '(' || line[i] == ')' || \
						line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == ';')
					{
						if (somethingelse == true)
						{
							word += line[i];
							somethingelse = false;
							i++;
							break;
						}
						somethingelse = true;
						break;
					}
					if (line[i] == ' ') { i++; break; }
					if (line[i] == 0x27)
					{
						for (int j = line.find("'", i + 1); i < j + 1; i++)
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
					FST::FST integer(words, fst_integer); if (FST::execute(integer)) { LexTable << "t"; InfinityCycle = 0; break;   }
					//string  
					FST::FST strg(words, fst_string); if (FST::execute(strg)) { LexTable << "t"; InfinityCycle = 0; break;  }
					//function 
					FST::FST func(words, fst_function); if (FST::execute(func)) { LexTable << "f"; InfinityCycle = 0; break;  }
					//declare 
					FST::FST declare(words, fst_declare); if (FST::execute(declare)) { LexTable << "d"; InfinityCycle = 0; break;  }
					//return 
					FST::FST retrn(words, fst_return); if (FST::execute(retrn)) { LexTable << "r"; InfinityCycle = 0; break;  }
					//print 
					FST::FST prnt(words, fst_print); if (FST::execute(prnt)) { LexTable << "p"; InfinityCycle = 0; break;  }
					//main 
					FST::FST mmain(words, fst_main); if (FST::execute(mmain)) { LexTable << "m"; InfinityCycle = 0; break;  }
					//arifm 
					FST::FST arifm(words, fst_arifm); if (FST::execute(arifm)) { LexTable << "v"; InfinityCycle = 0; break;  }
					//int literal 
					FST::FST integerliteral(words, fst_integer_literal); if (FST::execute(integerliteral)) { LexTable << "l"; InfinityCycle = 0; break;  }
					//string literal 
					FST::FST strngliteral(words, fst_string_literal); if (FST::execute(strngliteral)) { LexTable << "l"; InfinityCycle = 0; break;  }
					// ( 
					FST::FST rightbrace(words, fst_right_bracket); if (FST::execute(rightbrace)) { LexTable << ")"; InfinityCycle = 0; break;  }
					// ) 
					FST::FST leftbrace(words, fst_left_bracket);  if (FST::execute(leftbrace)) { LexTable << "("; InfinityCycle = 0; break;  }
					// } 
					FST::FST rightcurlybrace(words, fst_curly_right_bracket); if (FST::execute(rightcurlybrace)) { LexTable << "}"; InfinityCycle = 0; break;  }
					// { 
					FST::FST leftcurlybrace(words, fst_curly_left_bracket); if (FST::execute(leftcurlybrace)) { LexTable << "{"; InfinityCycle = 0; break;  }
					// comma 
					FST::FST comma(words, fst_comma); if (FST::execute(comma)) { LexTable << ","; InfinityCycle = 0; break;  }
					//comma dot 
					FST::FST commadot(words, fst_comma_dot); if (FST::execute(commadot)) { LexTable << ";"; InfinityCycle = 0; break;  }
					// equal
					FST::FST equal(words, fst_equal); if (FST::execute(equal)) { LexTable << "="; InfinityCycle = 0; break;  }
					//idenf
					FST::FST idenf(words, fst_idenf); if (FST::execute(idenf)) { LexTable << "i"; InfinityCycle = 0; break;  }

				}
				if (InfinityCycle > 5) { ERROR_THROW_IN(120, 0, 0); }
				delete words;

			}
			LexTable << "\n";
		}

	}



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
		bool isfunction = false, isdeclare = false, function = false;
		int lexemcounter = 0, idenfscounter=0;
		int sepline = 0;
		int scope=0, subscope=0, maxscope=0;
		bool isequal = false;
		

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
						line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == ';')
					{
						if (somethingelse == true)
						{
							word += line[i];
							somethingelse = false;
							i++;
							break;
						}
						somethingelse = true;
						break;
					}
					if (line[i] == ' ') { i++; break; }
					if (line[i] == 0x27)
					{
						for (int j = line.find("'", i + 1); i < j + 1; i++)
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
						
						if (scope == 0) { scope = maxscope + 1; maxscope++; }
						else 
						{
							subscope++;
						}


						type = 2;
						isfunction = true;
						function = true;
						InfinityCycle = 0; 
						break; 
					}
					//declare 
					FST::FST declare(words, fst_declare); if (FST::execute(declare)) 
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
						if (scope == 0) { scope = maxscope + 1; maxscope++; }
						else
						{
							subscope++;
						}
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
					//int literal 
					FST::FST integerliteral(words, fst_integer_literal); if (FST::execute(integerliteral)) 
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LITERAL;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						
						if (lexems.table[lexemcounter - 1].lexema == "=") 
						{
							if (idenfs.table[idenfscounter - 1].datatype == 1) 
							{
								idenfs.table[idenfscounter - 1].value.vint = atoi(word.c_str());
							}
							else { ERROR_THROW_IN(123, sepline + separat(separators, sepcount, i), 0); }
						}
						else 
						{
							idenfscounter++;
							IT::Entry idenf;
							idenf.name = "lit";
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
							idenf.value.vint = atoi(word.c_str());
							IT::Add(idenfs, idenf);


						}


						InfinityCycle = 0;
						break; 
					
					}
					//string literal 
					FST::FST strngliteral(words, fst_string_literal); if (FST::execute(strngliteral)) 
					{
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_LITERAL;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						if (lexems.table[lexemcounter - 2].lexema == "=")
						{
							if (idenfs.table[idenfscounter - 1].datatype == 2)
							{
								word = word.substr(1, word.length() - 2);


								strcpy(idenfs.table[idenfscounter - 1].value.vstr->str, word.c_str());
								idenfs.table[idenfscounter - 1].value.vstr->len = word.length();
							}
							else { ERROR_THROW_IN(123, sepline + separat(separators, sepcount, i), 0); }
						}
						else 
						{
							idenfscounter++;
							IT::Entry idenf;
							idenf.name = "lit";
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
							word = word.substr(1, word.length() - 2);


							strcpy(idenf.value.vstr->str, word.c_str());
							idenf.value.vstr->len = word.length();
							IT::Add(idenfs, idenf);
						
						}




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
					
						

						isfunction = false;
						if (subscope > 0 && isdeclare == true)
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
							idenfs.table[idenfscounter-1].type = 2;
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
						lexem.linenumber = sepline+ separat(separators, sepcount, i);
						lexem.indexTI = LT_TI_NULLIDX;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);
						if (subscope != 0) 
						{
							fun = prevfun;
						}
						else 
						{
							prevfun = fun;
							fun = "";
						}
						if (subscope == 0) {scope = 0;}
						else { subscope--; }
						
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
					FST::FST idenf(words, fst_idenf); if (FST::execute(idenf)) 
					{	
						idenfscounter++;
						lexemcounter++;
						LT::Entry lexem;
						lexem.lexema = LEX_ID;
						lexem.linenumber = sepline + separat(separators, sepcount, i);
						lexem.indexTI = idenfscounter-1;
						lexem.IlLine = linecounter;
						LT::Add(lexems, lexem);

						if (isfunction == true && function == false)
						{
							type = 3;

						}

						//Дописывание функции спереди идентефикатора
						if (type == 2 && isdeclare==false) 
						{
							if (fun == "") { prevfun = fun; }
							fun = word;
							if (subscope != 0) { word = prevfun + word; }
						}
						else 
						{
							word = fun + word;
						}
						if (subscope != 0) { word = prevfun + word; }
					
						
						//check for keywords
						if (word == "lit") { ERROR_THROW_IN(116, sepline + separat(separators, sepcount, i), 0); }


						function = false;
						if (word.length() > 5) { word = word.substr(0, 5); }
						//check for big letter
						for (int j = 0; j < word.length(); j++) 
						{
							if (word[j] != tolower(word[j])) { ERROR_THROW_IN(115, sepline + separat(separators, sepcount, i), 0); }
						}
						
						
						IT::Entry idenf;
						idenf.name = word;
						idenf.scope = scope;
						idenf.subscope = subscope;
						idenf.type = type;
						idenf.datatype = datatype;
						if (idenfscounter >= 1) {
							
							if (idenfscounter > 1 && IT::IsId(idenfs, word,scope,subscope) < IT_NULLIDX)
							{
								idenf.indexfirstLE = IT::IsId(idenfs, word,scope,subscope);
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
				if (InfinityCycle > 5) { ERROR_THROW_IN(120, sepline + separat(separators, sepcount,i), 0); }

				
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
				sep = sepcount-i;
				return sep;
			}

		}
		return 1;
	}

	void DisplayLT(LT::LexTable lexems) 
	{
		int curLine=1;
		LT::Entry lexem;
		for (int i = 1; i < lexems.size+1; i++) 
		{
			
			lexem = LT::GetEntry(lexems, i);
			if (lexem.linenumber > curLine) { std::cout << "\n"; curLine = lexem.linenumber; }
			std::cout << lexem.lexema;
		}

	}

	void DisplayIT(IT::IdTable idenfs) 
	{
		IT::Entry idenf;
		for (int i = 1; i < idenfs.size+1; i++) 
		{
			idenf = IT::GetEntry(idenfs, i);

			std::cout
				<< "  name - " << idenf.name
				<< "  type - " << idenf.type
				<< "  datatype - " << idenf.datatype
				<< "  scope - " << idenf.scope << "-" << idenf.subscope
				<< "  first in LE - " << idenf.indexfirstLE 
				<< " value - ";
			
			switch (idenf.datatype) 
			{
			case 1: 
				std::cout << idenf.value.vint;
				break;
			

			case 2: 
				for (int j = 0; j < idenf.value.vstr->len && (int)idenf.value.vstr->str[j]!=-52; j++)
				{
					std::cout << idenf.value.vstr->str[j];
				}
				break;
			}
			
			std::cout << "\n";
			//не забудь потом про value
		}
	}




	//Для польско записи
	std::string LexPolish(std::string line)
	{

		
		std::string word;
		std::fstream LexTable;
		std::string FinalLine;
		word = "";
		int i = 0; // counter for line
		bool somethingelse = false;
		int linecounter = 0;


		while (i != line.length())
		{
			word = "";
			for (; i < line.length(); i++)
			{
				if (line[i] == ',' || line[i] == '(' || line[i] == ')' || \
					line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == ';')
				{
					if (somethingelse == true)
					{
						word += line[i];
						somethingelse = false;
						i++;
						break;
					}
					somethingelse = true;
					break;
				}
				if (line[i] == ' ') { i++; break; }
				if (line[i] == 0x27)
				{
					for (int j = line.find("'", i + 1); i < j + 1; i++)
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
			for (int j = 0; j < 1; j++) {
				//integer 
				FST::FST integer(words, fst_integer); if (FST::execute(integer)) { FinalLine += "t"; break; }
				//string  
				FST::FST strg(words, fst_string); if (FST::execute(strg)) { FinalLine += "t"; break; }
				//function 
				FST::FST func(words, fst_function); if (FST::execute(func)) { FinalLine += "f"; break; }
				//declare 
				FST::FST declare(words, fst_declare); if (FST::execute(declare)) { FinalLine += "d"; break; }
				//return 
				FST::FST retrn(words, fst_return); if (FST::execute(retrn)) { FinalLine += "r"; break; }
				//print 
				FST::FST prnt(words, fst_print); if (FST::execute(prnt)) { FinalLine += "p"; break; }
				//main 
				FST::FST mmain(words, fst_main); if (FST::execute(mmain)) { FinalLine += "m"; break; }
				//arifm 
				FST::FST arifm(words, fst_arifm); if (FST::execute(arifm)) { FinalLine += words[0]; break; }
				//int literal 
				FST::FST integerliteral(words, fst_integer_literal); if (FST::execute(integerliteral)) { FinalLine += "l"; break; }
				//string literal 
				FST::FST strngliteral(words, fst_string_literal); if (FST::execute(strngliteral)) { FinalLine += "l"; break; }
				// ( 
				FST::FST rightbrace(words, fst_right_bracket); if (FST::execute(rightbrace)) { FinalLine += ")"; break; }
				// ) 
				FST::FST leftbrace(words, fst_left_bracket);  if (FST::execute(leftbrace)) { FinalLine += "("; break; }
				// } 
				FST::FST rightcurlybrace(words, fst_curly_right_bracket); if (FST::execute(rightcurlybrace)) { FinalLine += "}"; break; }
				// { 
				FST::FST leftcurlybrace(words, fst_curly_left_bracket); if (FST::execute(leftcurlybrace)) { FinalLine += "{"; break; }
				// comma 
				FST::FST comma(words, fst_comma); if (FST::execute(comma)) { FinalLine += ","; break; }
				//comma dot 
				FST::FST commadot(words, fst_comma_dot); if (FST::execute(commadot)) { FinalLine += ";"; break; }
				// equal
				FST::FST equal(words, fst_equal); if (FST::execute(equal)) { FinalLine += "="; break; }
				//idenf
				FST::FST idenf(words, fst_idenf); if (FST::execute(idenf)) { FinalLine += "i"; break; }

			}
			delete words;

		}
		return FinalLine;
	}

	
}





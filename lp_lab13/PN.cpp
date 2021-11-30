#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include "Log.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "PN.h"
#include "LEX.h"

namespace PN
{

	void Polish(wchar_t infile[]) 
	{
		std::fstream input; input.open(infile, std::ios::in);
		if (!input) { throw ERROR_THROW(113) }
		std::fstream Idenfs; Idenfs.open("IdenfTable.txt", std::ios::in);


		std::string fullfile= "";
		std::string line;
		std::string sline;
		std::string ResLine = "";
		std::string stack = "";
		int numbline;
		int linecounter=0;
		while (getline(input, line)) 
		{
			ResLine = "";
			stack = "";
			linecounter++;
			sline = "";
			



			
			
			if (line.find("=") < 15) {}
			else {
				fullfile += line + "\n";
				continue;
			}
		

			
			//поиск строки из файла с иденфами и составление новой лексемы, но со знаками
			numbline = atoi(line.substr(0, 3).c_str());
			while (getline(Idenfs, sline)) 
			{
				if (atoi(sline.substr(0, 4).c_str()) == numbline) 
				{ 
					line = "";
					for (int k = sline.find("v_") +2; k < sline.length(); k++) 
					{
						line += sline[k];
					}
					break; 
				}
			
			
			
			}
			//Лексема, но со знаками
			line = LEX::LexPolish(line);
		//

			for (int j = 0; j < line.length(); j++) 
			{
				if (prior(line, j) == prior(line, j + 1)) 
				{
					ERROR_THROW_IN(126, linecounter, 0);
				}

			}

			std::string oper = "";
			//цикл разбора строки
			for (int i = 0; i < line.length(); i++) 
			{
				
				
				if (prior(line, i) < 0) 
				{ 
					if (line[i] == ',') { continue; }
					if (line[i] == 'i' && line[i + 1] == '(') { continue; }
					//ResLine.insert(ResLine.length(), line, i, 1);
					ResLine += line[i]; 
				}
				else 
				{
					//запись операции в stack
					if (stack == "" || stack[0] == '(' || line[i]== '(' && prior(line,i)>0) {
						if (line[i] == '(' && line[i - 1] == 'i')
						{
							stack.insert(0, "@");
						}
						else {
							stack.insert(0, line, i, 1);
						}
						 }
					else 
					{
						//выкидывание операций
						if (prior(line, i) > 1 ) 
						{
							while (prior(line, i) == prior(stack, 0) || prior(line, i) > prior(stack, 0)) 
							{
								
								if (stack != "")
								{ 
									ResLine += stack[0];
									stack = stack.substr(1, stack.length()); 
								}
								else {
									break;
								}
								
							}
							stack.insert(0, line, i, 1);
							continue;
						}

						//для скобок
						if (line[i] == ')') 
						{
							//записываю в результирающую строку стэк до скобки
							for (int j = 0; j < stack.length(); j++) 
							{
								if (stack[j] == '(' || stack[j] == '@')
								{
									if (stack[j] == '@') { ResLine += stack[j]; }
									break; 
								}
								ResLine += stack[j];
								//
							}
							//убирают из стека всё до скобки
							for (int j = 0; j < stack.length(); j++) 
							{
							if(stack[0]=='(' || stack[0] == '@')
							{
								stack = stack.substr(1, stack.length());
								break;
							}
							stack = stack.substr(1,stack.length());
							continue;
							}
							
						}
					
					}
				}

				if (i == line.length() - 1) 
				{
					while (stack != "") 
					{
						ResLine += stack[0];
						stack = stack.substr(1, stack.length());
					}
				
				}
			}


			for (int j = 0; j < ResLine.length(); j++) 
			{
				if (prior(ResLine, j) > 1) { ResLine[j] = 'v'; }
			}


			if (linecounter < 10)
			{
				fullfile +=  "00" + std::to_string(linecounter) + " ";
			}
			else if (linecounter < 100)
			{
				fullfile +=  "0" + std::to_string(linecounter) + " ";
			}
			else if (linecounter < 1000)
			{
				fullfile +=  std::to_string(linecounter)+ " ";
			}
			fullfile += "i="+ ResLine + ";\n";
			//std::cout << ResLine << std::endl;

		}
		input.close();

		input.open(infile, std::ios::out);
		input << fullfile;

		
	}

	void PolishNT(wchar_t infile[], LT::LexTable lexems, IT::IdTable idenfs)
	{
		std::fstream input; input.open(infile, std::ios::in);
		if (!input) { throw ERROR_THROW(113) }
		std::fstream Idenfs; Idenfs.open("IdenfTable.txt", std::ios::in);


		std::string fullfile = "";
		std::string line;
		std::string sline;
		std::string ResLine = "";
		std::string stack = "";
		int firstposition=-1,lastposition=0;
		bool findequal = false;
		int j = 0;
			while (j < lexems.size) {
		for (; j < lexems.size; j++) // граница нужной строки после равно
		{
			LT::Entry lexem;
			lexem = LT::GetEntry(lexems, j);
			if (lexem.lexema == LEX_EQUAL)
			{
				firstposition = j + 1; findequal = true;
			}
			if (lexem.lexema == LEX_SEMICOLON && firstposition > lastposition) 
			{
				lastposition = j - 1; break;
			}
		}
		if(findequal==false)
		{
			return;
		}
		findequal = false;
		int i = firstposition;
		int numbline;
		int linecounter = 0;
		LT::LexTable PolishLexems = LT::Create(lastposition+1 - firstposition);

		
		for (int m = 0; m < 1; m++) {
			bool braceopen = false;
			int k = firstposition;
			for (; k < lastposition + 1; k++)
			{
				std::cout << lexems.table[k - 1].lexema;
				if (priorNT(lexems, k ) == 1)
				{
					switch (braceopen) {
					case true: braceopen = false; break;

					case false: braceopen = true; break;
					}

				}
				if (priorNT(lexems, k) < -1 && k != firstposition)
				{
					
					if (priorNT(lexems, k - 1) == 1 && priorNT(lexems, k - 2) < 1 && priorNT(lexems, k - 2) != -2)
					{
						ERROR_THROW_IN(126, lexems.table[k - 1].linenumber, 0);
					}

					if (priorNT(lexems, k - 1) < 0 && priorNT(lexems, k - 1) != -1)
					{

						ERROR_THROW_IN(126, lexems.table[k - 1].linenumber, 0);
					}

				}
				if (priorNT(lexems, k) == priorNT(lexems, k + 1))
				{
					ERROR_THROW_IN(126, lexems.table[k - 1].linenumber, 0);
				}


			}
			if (braceopen == true) 
			{ 
				ERROR_THROW_IN(126, lexems.table[k - 1].linenumber, 0); 
			}
		}
		
			ResLine = "";
			stack = "";
			linecounter++;
			sline = "";





			

			

			
			//цикл разбора строки
			for (; i < lastposition+1; i++)
			{


				if (priorNT(lexems, i) < 0)
				{
					if (lexems.table[i-1].lexema == ",") { continue; }
					if (lexems.table[i - 2].lexema == "i" && lexems.table[i - 1].lexema == "(") { continue; }
					//ResLine.insert(ResLine.length(), line, i, 1);
					LT::Entry lexem;
					lexem = lexems.table[i - 1];
					LT::Add(PolishLexems,lexem);
				}
				else
				{
					//запись операции в stack
					if (stack == "" || stack[0] == '(' || lexems.table[i - 1].lexema == "(" && priorNT(lexems, i) > 0) {
						if (lexems.table[i - 1].lexema == "(" && lexems.table[i - 2].lexema == "i")
						{
							PolishLexems.size--;
							stack.insert(0, "@");
						}
						else {
							stack.insert(0, lexems.table[i - 1].lexema);
						}
					}
					else
					{
						//выкидывание операций
						if (priorNT(lexems, i) > 1)
						{
							while (priorNT(lexems, i) == prior(stack, 0) || priorNT(lexems, i) > prior(stack, 0))
							{

								if (stack != "")
								{
									LT::Entry lexem;
									lexem.lexema = stack[0];
									lexem.indexTI = lexems.table[i - 1].indexTI;
									lexem.linenumber = lexems.table[i - 1].linenumber;
									LT::Add(PolishLexems, lexem);

								
									stack = stack.substr(1, stack.length());
								}
								else {
									break;
								}

							}
							stack.insert(0, lexems.table[i - 1].lexema);
							continue;
						}

						//для скобок
						if (lexems.table[i - 1].lexema == ")")
						{
							//записываю в результирающую строку стэк до скобки
							for (int j = 0; j < stack.length(); j++)
							{
								if (stack[j] == '(' || stack[j] == '@')
								{
									if (stack[j] == '@') 
									{
										LT::Entry lexem;
										lexem.lexema = stack[j];
										lexem.indexTI = lexems.table[i - 1].indexTI;
										lexem.linenumber = lexems.table[i - 1].linenumber;
										LT::Add(PolishLexems, lexem);
									}
									break;
								}
								LT::Entry lexem;
								lexem.lexema = stack[j];
								lexem.indexTI = lexems.table[i - 1].indexTI;
								lexem.linenumber = lexems.table[i - 1].linenumber;
								LT::Add(PolishLexems, lexem);
								//
							}
							//убирают из стека всё до скобки
							for (int j = 0; j < stack.length(); j++)
							{
								if (stack[0] == '(' || stack[0] == '@')
								{
									stack = stack.substr(1, stack.length());
									break;
								}
								stack = stack.substr(1, stack.length());
								continue;
							}

						}

					}
				}

			
			}
			if (stack != "") 
			{
				for (int k = 0; k < stack.length(); k++) 
				{
					LT::Entry lexem;
					lexem.lexema = stack[k];
					lexem.indexTI = lexems.table[i - 1].indexTI;
					lexem.linenumber = lexems.table[i - 1].linenumber;
					LT::Add(PolishLexems, lexem);
					stack = stack.substr(1, stack.length());
				}

			}


			for (int k = firstposition, l = 1; l < PolishLexems.size + 1; k++,l++) 
			{
				/*if (PolishLexems.table[l - 1].lexema == "+" || PolishLexems.table[l - 1].lexema == "-" || PolishLexems.table[l - 1].lexema == "*" || PolishLexems.table[l - 1].lexema == "/") 
				{
					PolishLexems.table[l-1].lexema = "v";
				}*/
				lexems.table[k - 1] = PolishLexems.table[l - 1];
				i = k+1;
			}

			if (i < lastposition + 1) 
			{
				for (; i < lastposition + 1; i++) 
				{
					lexems.table[i - 1].lexema = "A";
				}
			}
			
			
		
			
			j++;
		}
		input.close();

		input.open(infile, std::ios::out);
		input << fullfile;


	}


	int priorNT(LT::LexTable lexems,int i) 
	{
		if (lexems.table[i - 1].lexema  == ")" || lexems.table[i - 1].lexema  == "(") { return 1; }
		if (lexems.table[i - 1].lexema  == "-" || lexems.table[i - 1].lexema  == "+") { return 2; }
		if (lexems.table[i - 1].lexema  == "/" || lexems.table[i - 1].lexema  == "*") { return 3; }
		if (lexems.table[i - 1].lexema == "i") { return -2; }
		if (lexems.table[i - 1].lexema == "l") { return -3; }
		return -1;
	}



	int prior(std::string line, int pos) 
	{
	
		if (line[pos] == ')' || line[pos] == '(') { return 1; }
		if (line[pos] == '-' || line[pos] == '+') { return 2; }
		if (line[pos] == '/' || line[pos] == '*') { return 3; }
		if (line[pos] == 'l' || line[pos] == 'i') { return -2; }
		return -1;
	}


}
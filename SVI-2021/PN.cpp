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

	

	void PolishNT(LT::LexTable lexems, IT::IdTable idenfs)
	{
		std::string fullfile = "";
		std::string ResLine = "";
		std::string stack = "";
		int firstposition=-1,lastposition=0;
		bool findequal = false;
		int j = 1;
			while (j < lexems.size) {
		for (; j < lexems.size; j++) // ??????? ??????? ????????? ????? ?????
		{
			LT::Entry lexem;
			lexem = LT::GetEntry(lexems, j);
			if (lexem.lexema == LEX_EQUAL)
			{
				if (LT::GetEntry(lexems, j + 1).lexema == LEX_EQUAL) { j++; }
				else {
					firstposition = j + 1; findequal = true;
				}
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
			//???????? ????????? ?? ??????
			for (; k < lastposition + 1; k++)
			{
				
				if (priorNT(lexems, k ) == 1)
				{
					switch (braceopen) {
					case true: braceopen = false; break;

					case false: braceopen = true; break;
					}

				}
				if (priorNT(lexems, k) < -1 && k != firstposition)
				{
					
					if (priorNT(lexems, k - 1) == 1 && priorNT(lexems, k - 2) < 1 && priorNT(lexems, k - 2) != -2 && priorNT(lexems, k - 2) != -1)
					{
						ERROR_THROW_IN(304, lexems.table[k - 1].linenumber, 0);
					}

					if (priorNT(lexems, k - 1) < 0 && priorNT(lexems, k - 1) != -1)
					{

						ERROR_THROW_IN(304, lexems.table[k - 1].linenumber, 0);
					}

				}
			}
			if (braceopen == true) 
			{ 
				ERROR_THROW_IN(304, lexems.table[k - 1].linenumber, 0); 
			}
		}
		
			ResLine = "";
			stack = "";
			linecounter++;





			

			

			
			//???? ??????? ?????????
			for (; i < lastposition+1; i++)
			{
				if (priorNT(lexems, i) < 0)
				{
					if (lexems.table[i-1].lexema == ",") { continue; }
					if (lexems.table[i - 2].lexema == "i" && lexems.table[i - 1].lexema == "(") 
					{	continue; }
					if (lexems.table[i - 1].lexema == "i" && lexems.table[i].lexema == "(") 
					{
						for (; lexems.table[i - 2].lexema != LEX_RIGHTHESIS; i++)
						{
							ResLine += lexems.table[i - 1].lexema;
							LT::Entry lexem;
							lexem = lexems.table[i - 1];
							LT::Add(PolishLexems, lexem);
						}
						i--;
						continue;
					}
					LT::Entry lexem;
					lexem = lexems.table[i - 1];
					LT::Add(PolishLexems,lexem);
				}
				else
				{
					//?????? ???????? ? stack
					if (stack == "" || stack[0] == '(' || lexems.table[i - 1].lexema == "(" && priorNT(lexems, i) > 0) {
						if (lexems.table[i - 1].lexema == "(" && lexems.table[i - 2].lexema == "i")
						{
						}
						else {
							stack.insert(0, lexems.table[i - 1].lexema);
						}
					}
					else
					{
						//??????????? ????????
						if (priorNT(lexems, i) > 1)
						{
							while (priorNT(lexems, i) == prior(stack, 0) || priorNT(lexems, i) < prior(stack, 0))
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
						//??? ??????
						if (lexems.table[i - 1].lexema == ")")
						{
							//????????? ? ???????? ?????? ???? ?? ??????
							for (int j = 0; j < stack.length()+1; j++)
							{
								if (stack[j] == '(')
								{
									break;
								}
								LT::Entry lexem;
								lexem.lexema = stack[j];
								lexem.indexTI = lexems.table[i - 1].indexTI;
								lexem.linenumber = lexems.table[i - 1].linenumber;
								LT::Add(PolishLexems, lexem);
							
							}
							//??????? ?? ????? ??? ?? ??????
							for (int j = 0; j < stack.length()+2; j++)
							{
								if (stack[0] == '(')
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
				for (int k = 0; ;) 
				{
					
					if (stack == "") { break; }
					LT::Entry lexem;
					lexem.lexema = stack[k];
					lexem.indexTI = lexems.table[i - 1].indexTI;
					lexem.linenumber = lexems.table[i - 1].linenumber;
					LT::Add(PolishLexems, lexem);
					stack = stack.substr(1, stack.length());
				}

			}

			//?????? ????????? ? ??????? ?????? ? ???????? ??????
			for (int k = firstposition, l = 1; l < PolishLexems.size + 1; k++,l++) 
			{


				lexems.table[k - 1] = PolishLexems.table[l - 1];
				i = k+1;
			}
			if (i < lastposition + 1) 
			{
				//?????? ?????? ?????????
				for (; i < lastposition + 1; i++) 
				{
					lexems.table[i - 1].lexema = "A";
				}
			}


			j++;
		}


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
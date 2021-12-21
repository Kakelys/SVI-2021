#include "GEN.h"
















std::string StartWork(LT::LexTable lexems, IT::IdTable idenfs)
{
	std::string str=""; //Основная строка, которую буду заполнять
	std::string temp;
	str += START;
	str += EXTERN;
	

	std::string ForConst = CONST; 
	std::string ForData = DATA; 
		
	for (int i = 0; i < idenfs.size; i++) 
	{
		IT::Entry elem = idenfs.table[i];
		temp = "\t\t" + elem.name;

		if (elem.type == 4) //литарал
		{
			switch (elem.datatype)
			{
			case 1: temp = temp + " sdword " + std::to_string(elem.value.vint); break;
			case 2: temp = temp + " byte '" + std::string(elem.value.vstr->str) + "', 0"; break;
			}
			ForConst += temp + "\n";
		
		}
		else if (elem.type == 1) 
		{
			if (IT::AlredyExist(idenfs, i, elem.name)) { continue; }
			switch (elem.datatype)
			{
			case 1: temp = temp + " sdword 0" ; break;
			case 2: temp = temp + " dword ?"; break;
			}
			ForData += temp + "\n";
		}
	
		
	}
	str += ForConst;
	str += ForData;
	str += CODE;
	return str;
}

std::string genFucntion(LT::LexTable lexems, IT::IdTable idenfs, int i, std::string func, int ParmCount) 
{
	std::string str;

	IT::Entry elem = idenfs.table[lexems.table[i + 1].indexTI];

	str = elem.name + " PROC, \n\t";

	//Запись параметров
	int j = i + 3;
	while (lexems.table[j].lexema != LEX_RIGHTHESIS)
	{
		if (lexems.table[j].lexema == LEX_ID)
		{
			str += idenfs.table[lexems.table[j].indexTI].name + (idenfs.table[lexems.table[j].indexTI].datatype == 1 ? " : sdword, " : " : dword,  ");
		}
		j++;
	}


	
	//Удаление лишней запятой
	int k = str.rfind(',');
	if (k > 0) { str[k] = ' '; }

	str += "\npush ebx\npush edx\n";
	return str;

}

std::string genCallFunction(LT::LexTable lexems, IT::IdTable idenfs, int i) 
{
	std::string str;
	IT::Entry elem = idenfs.table[lexems.table[i].indexTI];
	std::stack<IT::Entry> tmp;

	for (int j = i + 1; lexems.table[j].lexema != LEX_RIGHTHESIS; j++) 
	{
		if (lexems.table[j].lexema == LEX_ID || lexems.table[j].lexema == LEX_LITERAL) 
		{
			tmp.push(idenfs.table[lexems.table[j].indexTI]);//заполняем стек
		}
	}
	str += "\n";

	while (!tmp.empty()) 
	{
		if (tmp.top().type == 4 && tmp.top().datatype == 2) 
		{
			str += "push offset " + tmp.top().name + "\n";
		}
		else
		{
			str += "push " + tmp.top().name + "\n";
		}
		tmp.pop();
	}

	str += "call " + elem.name + " ";
	return str;
}

std::string genEqual(LT::LexTable lexems, IT::IdTable idenfs, int i)
{
	std::string str;
	IT::Entry elem1 = idenfs.table[lexems.table[i - 1].indexTI]; // левый id

	switch (elem1.datatype)
	{
	case 1: {
		for (int j = i + 1; lexems.table[j].lexema != LEX_SEMICOLON; j++)
		{
			switch (lexems.table[j].lexema[0])
			{
			
			case LITERAL:
			case ID:
			{
				if (idenfs.table[lexems.table[j].indexTI].type == 2)
				{
					str += genCallFunction(lexems, idenfs, j); //возврат в eax
					str += "\n";
					str = str + "push eax\n"; // закинуть в стек для дальнейшего вычисления
					while (lexems.table[j].lexema != LEX_RIGHTHESIS) { j++; }
					break;
				}
				else
				{
						str += "push " + idenfs.table[lexems.table[j].indexTI].name + "\n";
				}
				break;
			}
			case PLUS:
				str = str + "pop ebx\npop eax\nadd eax, ebx\npush eax\ntest ebx, MAX\njb over_flow\ntest ebx, MIN\nja over_flow\n"; break;
			case MINUS:
				str = str + "pop ebx\npop eax\nsub eax, ebx\npush eax\ntest ebx, MAX\njb over_flow\ntest ebx, MIN\nja over_flow\n"; break;
			case STAR:
				str = str + "pop ebx\npop eax\nimul eax, ebx\npush eax\ntest ebx, MAX\njb over_flow\ntest ebx, MIN\nja over_flow\n"; break;
			case DIRSLASH:
				str = str + "pop ebx\npop eax\ncdq\ntest ebx, ebx\njz div_by_0\nidiv ebx\npush eax\ntest ebx, MAX\nja over_flow\ntest ebx, MIN\njb over_flow\n"; break;
			}
			
				
		}
		
		str = str + "\npop ebx\nmov " + elem1.name + ", ebx\ntest ebx, MAX\njb over_flow\ntest ebx, MIN\nja over_flow\n";			
		break;
	}
	case 2: 
	{

		bool ConcatsBufferChange = false;
		for (int j = i + 1; lexems.table[j].lexema != LEX_SEMICOLON; j++)
		{
			switch (lexems.table[j].lexema[0])
			{

			case LITERAL:
			{
				str += "push offset " + idenfs.table[lexems.table[j].indexTI].name + "\n";
				break;
			}
			case ID:
			{
				if (idenfs.table[lexems.table[j].indexTI].type == 2)
				{
					str += genCallFunction(lexems, idenfs, j); //возврат в eax
					str += "\n";
					str = str + "push eax\n"; // закинуть в стек для дальнейшего вычисления
					while (lexems.table[j].lexema != LEX_RIGHTHESIS) { j++; }
					break;
				}
				else
				{

					str += "push " + idenfs.table[lexems.table[j].indexTI].name + "\n";
				}
				break;
			}
			case PLUS:
			{
				//Поочерёдная смена буфера(если использовать один и тот же буфер, то оно ломается)
				switch (ConcatsBufferChange) 
				{
				case true:str = str + "push offset buffer1\ncall concats\npush eax\n"; ConcatsBufferChange = false; break;

				case false:str = str + "push offset buffer2\ncall concats\npush eax\n"; ConcatsBufferChange = true; break;

				}
				
				//str = str + "pop ebx\npop eax\npush offset buffer\ncall concats\npush eax\n"; break;
			}
			}
		}
		str = str + "\npop ebx\nmov " + elem1.name + ", ebx\n";			// вычисленное выражение в ebx 
		break;


	
	}
	}
	str += "\n";
	return str;
}

std::string GenCallFunction(LT::LexTable lexems, IT::IdTable idenfs, int i)
{
	std::string str;
	IT::Entry elem = idenfs.table[lexems.table[i].indexTI];
	std::stack<IT::Entry> tmp;
	str += "\n";
	for (int j = i + 1; lexems.table[j].lexema != LEX_RIGHTHESIS; j++) 
	{
		if (lexems.table[j].lexema == LEX_ID || lexems.table[j].lexema == LEX_LITERAL) 
		{
			tmp.push(idenfs.table[lexems.table[j].indexTI]);
		}
	
	}


	while (!tmp.empty()) 
	{
		if (tmp.top().type == 4 && tmp.top().datatype == 2) 
		{
			str += "push offset " + tmp.top().name + "\n";
		}
		else 
		{
			str += "push " + tmp.top().name + "\n";
		}
		tmp.pop();
	}

	str += "call " + elem.name + " ";
	return str;
}

std::string genReturn(LT::LexTable lexems, IT::IdTable idenfs, int i, std::string func)
{

	std::string str = "\npop edx\npop ebx\n";
	if (lexems.table[i + 1].lexema != LEX_SEMICOLON) 
	{
		if (idenfs.table[lexems.table[i + 1].indexTI].datatype == 2)
		{
			str += "mov eax, offset " + idenfs.table[lexems.table[i + 1].indexTI].name + "\n";
			
		}
		else 
		{
			str += "mov eax, " + idenfs.table[lexems.table[i + 1].indexTI].name + "\n";
		}
		
		if (func == "main") 
		{
			return  "\npush "+ idenfs.table[lexems.table[i + 1].indexTI].name +"\ncall ExitProcess\ndiv_by_0:\ncall printline\npush offset ZERO\ncall printstr\npush - 1\ncall ExitProcess\nover_flow:\ncall printline\npush offset OVER\ncall printstr\npush - 1\ncall ExitProcess\nmain ENDP\nend main"; 
		}
	}




	str += "ret\n";
	str += "\ndiv_by_0:\ncall printline\npush offset ZERO\ncall printstr\npush - 1\ncall ExitProcess\nover_flow:\ncall printline\npush offset OVER\ncall printstr\npush - 1\ncall ExitProcess\n";

	str += func + " ENDP" + "\n";
	return str;
}
std::string GenPrint(LT::LexTable lexems, IT::IdTable idenfs, int& i)
{
	std::string str;
	IT::Entry elem = idenfs.table[lexems.table[i+1].indexTI];
	str += "\n";
	if (elem.type == 2) 
	{
		str+=	GenCallFunction(lexems,idenfs,++i);
		str += "\n";
		str += "push eax \n";
		switch (elem.datatype) 
		{
		case 1: str += "call printnumb"; break;
		case 2: str += "call printstr"; break;
		}
		str += "\n";
		return str;
	}
	else {
		switch (elem.datatype)
		{
		case 1:
		{
			str += "push " + elem.name + "\ncall printnumb";

			break;
		}
		case 2:
		{
			if (elem.type != 4) 
			{
				str += "push " + elem.name + "\ncall printstr";
			}
			else {
				str += "push offset " + elem.name + "\ncall printstr";
			}
			
			break;
		}
		}
		str += "\n";
		return str;
	}
}

std::string GenIf(LT::LexTable lexems, IT::IdTable idenfs, int i, int mark)
{
	
	std::string str = "\n";

	IT::Entry op1 = idenfs.table[lexems.table[i + 2].indexTI];
	int secondop = 0;
	while (lexems.table[i + secondop-1].lexema != LEX_IF_OP) { secondop++; }
	IT::Entry op2 = idenfs.table[lexems.table[i + secondop].indexTI];
	//Небольшой костыль для красоты
	enum OPER { big, less, equal, nonequal, big_equal, less_equal };
	std::string cond = lexems.table[i + secondop-1].condition;
	OPER op = equal;
	if (cond == DEQUAL) { op = equal; }
	else if (cond == NONEQUAL) { op = nonequal; }
	else if (cond == BIGGER) { op = big; }
	else if (cond == LESS) { op = less; }
	else if (cond == BIGGER_EQUAL) { op = big_equal; }
	else if (cond == LESS_EQUAL) { op = less_equal; }
	if (op1.type == 2) 
	{
		str += GenCallFunction(lexems, idenfs, i+2) + "\n";
		op1.name = "eax";
		if (op2.type == 2) 
		{
			str += "mov edx, eax\n";
			op1.name = "edx";
			str += GenCallFunction(lexems, idenfs, i + secondop) + "\n";
			op2.name = "eax";
		}
	}
	else 
	{
		if (op2.type == 2)
		{
			str += GenCallFunction(lexems, idenfs, i + secondop) + "\n";
			op2.name = "eax";
		}
	}





	switch (op) 
	{
	case equal:
	{
		str += "mov ebx, " + op2.name + "\n";
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "je " + "L"+std::to_string(mark+1) + "\n" + "jne " + "L" + std::to_string(mark + 2) + "\n";
		break;
	}
	case nonequal:
	{
		str += "mov ebx, " + op2.name + "\n";
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "jne " + "L" + std::to_string(mark + 1) + "\n" + "je " + "L" + std::to_string(mark + 2) + "\n";
		break;
	}
	case big:
	{
		str += "mov ebx, " + op2.name + "\n";
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "ja " + "L" + std::to_string(mark + 1) + "\n" + "jna " + "L" + std::to_string(mark + 2) + "\n";

		break;
	}
	case less:
	{
		str += "mov ebx, " + op2.name + "\n";
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "jb " + "L" + std::to_string(mark + 1) + "\n" + "jnb " + "L" + std::to_string(mark + 2) + "\n";

		break;
	}
	case big_equal:
	{
		str += "mov ebx, " + op2.name + "\n";
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "jae " + "L" + std::to_string(mark + 1) + "\n" + "jnae " + "L" + std::to_string(mark + 2) + "\n";

		break;
	}
	case less_equal: 
	{
		str += "mov ebx, " + op2.name + "\n";
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "jbe " + "L" + std::to_string(mark + 1) + "\n" + "jnbe " + "L" + std::to_string(mark + 2) + "\n";

		break;
	}

	
	}


	return str;
}


namespace GEN 
{


	void CodeGeneration(LT::LexTable lexems, IT::IdTable idenfs, LIB::LibTable lib, wchar_t outfile[])
	{
		std::string fullfile = StartWork(lexems, idenfs);
		std::fstream input; 
		input.open(outfile, std::ios::out);
		if (!input) { ERROR_THROW(114); }
	

		std::string str = "";
		//
		std::string func;
		int ParmCount;
		int MarkCounter = 0, AmountMarks = 0; // Счётчик для меток/общее кол-во меток
		std::stack<std::string> marks;

		for (int i = 0; i < lexems.size; i++) 
		{
			switch (lexems.table[i].lexema[0])
			{
			case MAIN:
			{
				func = "main";
				str = str + "main PROC\n";
				break;
			}
			case RETURN: 
			{
				str += genReturn(lexems, idenfs, i, func);
				break; 
			}
			case FUNCTION:
			{
				//Проверка на функцию из библиотеки
				bool fun_lib = false;
				for (int j = 0; j < lib.size+1; j++) 
				{
					if (idenfs.table[lexems.table[i + 1].indexTI].name == lib.table[j-1].name) { fun_lib = true; break; }
				}
				if (fun_lib == true) { break; }
				//
				func = idenfs.table[lexems.table[i + 1].indexTI].name;
				ParmCount = idenfs.table[lexems.table[i + 1].indexTI].ParmCount;
				str = genFucntion(lexems, idenfs, i, func, ParmCount);

				break; 
			}
			case EQUAL: 
			{
				str = genEqual(lexems,idenfs,i);
				while (lexems.table[++i].lexema != LEX_SEMICOLON);
				break; 
			}
			case PRINT:
			{
				str = GenPrint(lexems,idenfs, i);
				break; 
			}
			case ID:
			{
				if (lexems.table[i + 1].lexema == LEX_LEFTHESIS && lexems.table[i - 1].lexema != LEX_FUNCTION) 
				{
					str = GenCallFunction(lexems,idenfs,i);
					str += "\n";
				}
				break;
			}
			case IF:
			{
				MarkCounter += 2;
				str = GenIf(lexems,idenfs,i,AmountMarks);
				
				while (MarkCounter > 0)
				{
					marks.push("L"+std::to_string(AmountMarks + MarkCounter) + ":");
					MarkCounter--; 

				}
				AmountMarks += 2;
				while (lexems.table[i].lexema != LEX_RIGHTHESIS) { i++; }

				break;
				
			}
			case RIGHTBRACE: 
			{

				if (lexems.table[i + 1].lexema == LEX_ELSE)
				{
					
					marks.push("L" + std::to_string(AmountMarks+1) + ":");

					str = "\njmp L" + std::to_string(AmountMarks) + "\n";
					fullfile.replace(fullfile.find("L" + std::to_string(AmountMarks)) + 1,1,std::to_string(AmountMarks+1));
					AmountMarks++;
					i += 1;
				}
				else {
					if (!marks.empty())
					{
						str = "\n" + marks.top() + "\n";
						marks.pop();
					}
				}
			
				break;
			}
			case LEFTBRACE: 
			{
				if (!marks.empty())
				{
					str = "\n" + marks.top() + "\n";
					marks.pop();
				}
				
			
				break;
			}
			
			}
			
			if (!str.empty())
				fullfile += str;

			str.clear();
		
		}
		//fullfile += END;
		input << fullfile;


#ifdef DISPLAY

		std::cout << fullfile;

#endif // DEBUG

		
	}
}
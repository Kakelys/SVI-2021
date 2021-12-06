#include "GEN.h"
















std::string StartWork(LT::LexTable lexems, IT::IdTable idenfs)
{
	std::string str=""; //�������� ������, ������� ���� ���������
	std::string temp;
	str += START;
	str += EXTERN;
	

	std::string ForConst = CONST; 
	std::string ForData = DATA; 
		
	for (int i = 0; i < idenfs.size; i++) 
	{
		IT::Entry elem = idenfs.table[i];
		temp = "\t\t" + elem.name;

		if (elem.type == 4) //�������
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

	//������ ����������
	int j = i + 3;
	while (lexems.table[j].lexema != LEX_RIGHTHESIS)
	{
		if (lexems.table[j].lexema == LEX_ID)
		{
			str += idenfs.table[lexems.table[j].indexTI].name + (idenfs.table[lexems.table[j].indexTI].datatype == 1 ? " : sdword, " : " : dword,  ");
		}
		j++;
	}


	
	//�������� ������ �������
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
			tmp.push(idenfs.table[lexems.table[i].indexTI]);//��������� ����
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
	IT::Entry elem1 = idenfs.table[lexems.table[i - 1].indexTI]; // ����� id

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
					str += genCallFunction(lexems, idenfs, i); //������� � eax
					str = str + "push eax\n"; // �������� � ���� ��� ����������� ����������
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
				str = str + "pop ebx\npop eax\nadd eax, ebx\npush eax\n"; break;
			case MINUS:
				str = str + "pop ebx\npop eax\nsub eax, ebx\npush eax\n"; break;
			case STAR:
				str = str + "pop ebx\npop eax\nimul eax, ebx\npush eax\n"; break;
			case DIRSLASH:
				str = str + "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n"; break;

			}
		}
		str = str + "\npop ebx\nmov " + elem1.name + ", ebx\n";			// ����������� ��������� � ebx 
		break;
	}
	case 2: 
	{
		std::string lexema = lexems.table[i+1].lexema;
		IT::Entry elem2 = idenfs.table[lexems.table[i + 1].indexTI];
		if (lexema == LEX_ID && elem2.type == 4) // ����� �������
		{
			str += genCallFunction(lexems,idenfs, i + 1);
			str +=  "mov " + elem1.name + ", eax";
		}
		else if (lexema == LEX_LITERAL) // �������
		{
			str += "mov " + elem1.name + ", offset " + elem2.name;
		}
		else // ��(����������) - ����� �������
		{
			str += "mov ecx, " + elem2.name + "\nmov " + elem1.name + ", ecx";
		}


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
		str += "mov eax, " + idenfs.table[lexems.table[i + 1].indexTI].name + "\n";
		if (func == "main") 
		{
			return  "\npush "+ idenfs.table[lexems.table[i + 1].indexTI].name +"\ncall ExitProcess\nmain ENDP\nend main"; 
		}
	}
	str += "ret\n";
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
	IT::Entry op2 = idenfs.table[lexems.table[i + 4].indexTI];
	//��������� ������� ��� �������
	enum OPER { big, less, equal, nonequal, big_equal, less_equal };
	std::string cond = lexems.table[i + 3].condition;
	OPER op = equal;
	if (cond == DEQUAL) { op = equal; }
	else if (cond == NONEQUAL) { op = nonequal; }
	else if (cond == BIGGER) { op = big; }
	else if (cond == LESS) { op = less; }
	else if (cond == BIGGER_EQUAL) { op = big_equal; }
	else if (cond == LESS_EQUAL) { op = less_equal; }

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
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "jna " + "L" + std::to_string(mark + 1) + "\n" + "ja " + "L" + std::to_string(mark + 2) + "\n";

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
		str += "cmp " + op1.name + ", " + "ebx" + "\n" + "jnae " + "L" + std::to_string(mark + 1) + "\n" + "jae " + "L" + std::to_string(mark + 2) + "\n";

		break;
	}

	
	}


	return str;
}


namespace GEN 
{


	void CodeGeneration(LT::LexTable lexems, IT::IdTable idenfs) 
	{
		std::string fullfile = StartWork(lexems, idenfs);
		std::fstream input; 
		input.open(AssPath1, std::ios::out);
	

		std::string str = "";
		//
		std::string func;
		int ParmCount;
		int MarkCounter = 0, AmountMarks = 0; // ������� ��� �����/����� ���-�� �����
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
				

				break;
				
			}
			case RIGHTBRACE: 
			{
				if (!marks.empty())
				{
					str = "\n" + marks.top() + "\n";
					marks.pop();
				}
				//if (MarkCounter > 0) //���������� �����
				//{
				//	MarkCounter--; AmountMarks++;
				//	fullfile += "\nL" + std::to_string(AmountMarks) + ": \n";
				//}
			
				break;
			}
			case LEFTBRACE: 
			{
				if (!marks.empty())
				{
					str = "\n" + marks.top() + "\n";
					marks.pop();
				}
				//if (MarkCounter > 0) //���������� �����
				//{
				//	MarkCounter--; AmountMarks++;
				//	fullfile += "\nL" + std::to_string(AmountMarks) + ": \n";
				//}
			
				break;
			}
			
			}
			
			if (!str.empty())
				fullfile += str;

			str.clear();
		
		}
		//fullfile += END;
		input << fullfile;
		std::cout << fullfile;
	}
}
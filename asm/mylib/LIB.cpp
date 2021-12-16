#include <iostream>
#pragma warning(disable : 4996)
extern "C"
{
	int __stdcall linelength(char* str)
	{

		int length = 0;
		if (str == nullptr) { std::cout << std::endl; }
		else {
			for (int i = 0; str[i] != '\0'; i++)
			{
				length = length +1;
			}
		}


		return length;
	}

	int __stdcall factorial(int numb) 
	{
		int fact = 1;
		for (int i = 1; i <= numb; i++) 
		{
			fact *= i;
		}
		return fact;
	}

	int __stdcall printstr(char* str)
	{
		setlocale(LC_ALL, "RUSSIAN");
		if (str == nullptr) { std::cout << std::endl; }
		else {
			for (int i = 0; str[i] != '\0'; i++)
			{
				std::cout << str[i];
			}
		}
		return 0;
	}

	int __stdcall printnumb(int numb)
	{
		std::cout << numb;


		return 0;
	}

	char* __stdcall concats(char* buffer, char* str1, char* str2)
	{
		int i = NULL, len1 = NULL, len2 = NULL;
	
		for (int j = 0; str2[j] != '\0'; j++)
		{
			if (i == 255)
				break;
			buffer[i++] = str2[j];
		}
		for (int j = 0; str1[j] != '\0'; j++)
		{
			if (i == 255)
				break;
			buffer[i++] = str1[j];
		}
		buffer[i] = '\0';
		return buffer;
	}

	int __stdcall printline() 
	{
		std::cout << "\n";
		return 0;
	}
}
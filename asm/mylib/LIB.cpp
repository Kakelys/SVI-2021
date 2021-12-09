#include <iostream>

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
}
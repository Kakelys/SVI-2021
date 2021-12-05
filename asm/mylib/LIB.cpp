#include <iostream>

extern "C"
{
	int  line_length(int str)
	{
		return 0;
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
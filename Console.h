//
// Created by aragua on 2019.02.21..
//

#ifndef C_CONSOLE_H
#define C_CONSOLE_H

#include <iostream>

class Console
{
public:
	template<typename T>
	static void Write(const T &value)
	{
		std::cout << value;
	}
	
	template<typename T>
	static void WriteLine(const T &str)
	{
		Write(str);
		std::cout << std::endl;
	}
	
	static void WriteSeparator()
	{
		WriteLine("--------------------------------------------------------------------------------");
	}
	
	static char ReadKey()
	{
		char key;
		std::cin >> key;
		return key;
	}
};

#endif //C_CONSOLE_H

//
// Created by aragua on 2019.02.21..
//

#ifndef C_STRINGBUILDER_H
#define C_STRINGBUILDER_H


#include <sstream>

class StringBuilder
{
public:
	template<typename T>
	void Add(const T &value)
	{
		buffer << value;
	}
	
	template<typename T>
	StringBuilder &operator<<(const T &value)
	{
		Add(value);
		return *this;
	}
	
	StringBuilder &NewLine();
	
	std::string ToString() const;

private:
	std::ostringstream buffer;
};


#endif //C_STRINGBUILDER_H

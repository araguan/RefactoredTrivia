//
// Created by aragua on 2019.02.21..
//

#include "StringBuilder.h"

std::string StringBuilder::ToString() const
{
	return buffer.str();
}

StringBuilder &StringBuilder::NewLine()
{
	buffer << std::endl;
	return *this;
}

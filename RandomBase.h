//
// Created by aragua on 2019.02.20..
//

#ifndef C_RANDOMBASE_H
#define C_RANDOMBASE_H

#include "Enumerations.h"

class RandomBase
{
public:
	virtual RandomMode Mode() const = 0;
	
	size_t Next();

protected:
	RandomBase() = default;
	
	virtual size_t OnNext() = 0;
};


#endif //C_RANDOMBASE_H

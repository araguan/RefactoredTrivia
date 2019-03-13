//
// Created by aragua on 2019.03.08..
//

#ifndef C_RANDOMFACTORY_H
#define C_RANDOMFACTORY_H

#include <memory>
#include "Enumerations.h"

class RandomBase;

class RandomFactory
{
public:
	static std::shared_ptr<RandomBase> Create(const RandomMode &mode);
};


#endif //C_RANDOMFACTORY_H

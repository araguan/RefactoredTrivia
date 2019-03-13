//
// Created by aragua on 2019.03.11..
//

#include "RollProvider.h"
#include "Exceptions.h"
#include "Configuration.h"

RollProvider::RollProvider(std::shared_ptr<RandomBase> &random)
		: random(random)
{
	if (nullptr == random)
	{
		Throw(ArgumentNullException("random"));
	}
}

size_t RollProvider::RollNextValue()
{
	return random->Next() % MaxRollValue + 1;
}

std::shared_ptr<RandomBase> RollProvider::Random() const
{
	return random;
}

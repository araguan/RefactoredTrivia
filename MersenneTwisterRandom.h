//
// Created by aragua on 2019.03.07..
//

#ifndef C_MERSENNETWISTERRANDOM_H
#define C_MERSENNETWISTERRANDOM_H


#include <cstddef>
#include <random>
#include "RandomBase.h"

class MersenneTwisterRandom : public RandomBase
{
	friend class RandomFactory;

protected:
	RandomMode Mode() const override;
	
	size_t OnNext() override;

private:
	MersenneTwisterRandom();
	
	std::random_device randomDevice;
	std::mt19937_64 mersenneTwisterEngine;
	std::uniform_int_distribution<size_t> distribution;
};


#endif //C_MERSENNETWISTERRANDOM_H

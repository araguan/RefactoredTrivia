//
// Created by aragua on 2019.03.07..
//

#include "MersenneTwisterRandom.h"

MersenneTwisterRandom::MersenneTwisterRandom()
		: randomDevice(),
		  mersenneTwisterEngine(randomDevice()),
		  distribution(0, std::numeric_limits<size_t>::max())
{
}

size_t MersenneTwisterRandom::OnNext()
{
	return distribution(mersenneTwisterEngine);
}

RandomMode MersenneTwisterRandom::Mode() const
{
	return RandomMode::MersenneTwister;
}

//
// Created by aragua on 2019.03.08..
//

#include "RandomFactory.h"
#include "Exceptions.h"
#include "FixedLegacyRandom.h"
#include "TimeBasedLegacyRandom.h"
#include "MersenneTwisterRandom.h"

using namespace std;

shared_ptr<RandomBase> RandomFactory::Create(const RandomMode &mode)
{
	switch (mode)
	{
		case RandomMode::FixedLegacy:
		{
			return shared_ptr<RandomBase>(new FixedLegacyRandom());
		}
		
		case RandomMode::TimeBasedLegacy:
		{
			return shared_ptr<RandomBase>(new TimeBasedLegacyRandom());
		}
		
		case RandomMode::MersenneTwister:
		{
			return shared_ptr<RandomBase>(new MersenneTwisterRandom());
		}
		
		default:
		{
			Throw (InvalidOperationException("Unknown RandomMode."));
		}
	}
}

//
// Created by aragua on 2019.03.07..
//

#include <ctime>
#include <cstdlib>
#include "TimeBasedLegacyRandom.h"

TimeBasedLegacyRandom::TimeBasedLegacyRandom()
{
	time_t t;
	time(&t);
	
	seedCallCount++;
	t += seedCallCount;
	
	srand((unsigned int) t);
}

RandomMode TimeBasedLegacyRandom::Mode() const
{
	return RandomMode::TimeBasedLegacy;
}

//
// Created by aragua on 2019.03.07..
//

#include <cstdlib>
#include "FixedLegacyRandom.h"

FixedLegacyRandom::FixedLegacyRandom()
{
	srand(0);
}

RandomMode FixedLegacyRandom::Mode() const
{
	return RandomMode::FixedLegacy;
}

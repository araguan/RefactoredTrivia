//
// Created by aragua on 2019.03.07..
//

#ifndef C_TIMEBASEDLEGACYRANDOM_H
#define C_TIMEBASEDLEGACYRANDOM_H


#include <cstddef>
#include "LegacyRandomBase.h"

class TimeBasedLegacyRandom : public LegacyRandomBase
{
	friend class RandomFactory;

public:
	RandomMode Mode() const override;

private:
	TimeBasedLegacyRandom();
	
	static inline size_t seedCallCount = 0;
};


#endif //C_TIMEBASEDLEGACYRANDOM_H

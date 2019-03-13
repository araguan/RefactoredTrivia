//
// Created by aragua on 2019.03.07..
//

#ifndef C_FIXEDLEGACYRANDOM_H
#define C_FIXEDLEGACYRANDOM_H


#include <cstddef>
#include "LegacyRandomBase.h"

class FixedLegacyRandom : public LegacyRandomBase
{
	friend class RandomFactory;

protected:
	RandomMode Mode() const override;

private:
	FixedLegacyRandom();
};


#endif //C_FIXEDLEGACYRANDOM_H

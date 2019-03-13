//
// Created by aragua on 2019.03.07..
//

#ifndef C_LEGACYRANDOMBASE_H
#define C_LEGACYRANDOMBASE_H

#include <cstddef>
#include "RandomBase.h"

class LegacyRandomBase : public RandomBase
{
public:
	virtual ~LegacyRandomBase();

protected:
	LegacyRandomBase();
	
	size_t OnNext() override;

private:
	static inline size_t legacyRandomInstanceCount = 0;
};


#endif //C_LEGACYRANDOMBASE_H

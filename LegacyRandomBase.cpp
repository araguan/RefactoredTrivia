//
// Created by aragua on 2019.03.07..
//

#include "LegacyRandomBase.h"
#include "Exceptions.h"

LegacyRandomBase::LegacyRandomBase()
{
	if (1 <= legacyRandomInstanceCount)
	{
		Throw(InvalidOperationException(
				"No concurrent instances of legacy random classes are allowed to avoid inconclusive calls to C-style srand() & rand()."));
	}
	
	legacyRandomInstanceCount++;
}

LegacyRandomBase::~LegacyRandomBase()
{
	legacyRandomInstanceCount--;
}

size_t LegacyRandomBase::OnNext()
{
	return (size_t) rand();
}

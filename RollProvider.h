//
// Created by aragua on 2019.03.11..
//

#ifndef C_ROLLPROVIDER_H
#define C_ROLLPROVIDER_H


#include <memory>
#include "RandomBase.h"

class RollProvider
{
public:
	explicit RollProvider(std::shared_ptr<RandomBase> &random);
	
	std::shared_ptr<RandomBase> Random() const;
	
	size_t RollNextValue();

private:
	std::shared_ptr<RandomBase> random;
};


#endif //C_ROLLPROVIDER_H

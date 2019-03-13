//
// Created by aragua on 2019.02.20..
//

#ifndef C_PLAYER_H
#define C_PLAYER_H

#include <memory>
#include <string>
#include <bits/shared_ptr.h>
#include "RandomBase.h"
#include "Enumerations.h"
#include "RollProvider.h"
#include "PenaltyBoxLogic.h"

class Player
{
public:
	explicit Player(const std::string &name);
	
	std::string Name() const;
	
	size_t Gold() const;
	
	void IncrementGold();
	
	size_t Position() const;
	
	void IncrementPosition(size_t value);
	
	bool CanPlay();
	
	std::shared_ptr<PenaltyBoxLogic> PenaltyLogic();

private:
	const std::string name;
	size_t gold = 0;
	size_t position = 0;
	
	std::shared_ptr<PenaltyBoxLogic> penaltyLogic;
	
	void VerifyIncrementPositionValue(size_t value);
};


#endif //C_PLAYER_H

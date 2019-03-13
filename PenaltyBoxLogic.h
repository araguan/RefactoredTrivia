//
// Created by aragua on 2019.03.11..
//

#ifndef C_PENALTYBOXLOGIC_H
#define C_PENALTYBOXLOGIC_H


#include <cstddef>
#include "Enumerations.h"
#include "RollProvider.h"

class PenaltyBoxLogic
{
public:
	explicit PenaltyBoxLogic(const std::string &playerName);
	
	PenaltyStates State() const;
	
	void TryGetOutOfBoxOnDemand(size_t rollValue, std::shared_ptr<RollProvider> &rollProvider);
	
	void SendToBox();

private:
	const std::string playerName;
	PenaltyStates penaltyState = PenaltyStates::FreeToPlay;
	
	void TryGetOutOfBoxInternal(size_t rollValue);
	
	void CorrectFixedLegacyRandomSequenceOnDemand(std::shared_ptr<RollProvider> &rollProvider);
};


#endif //C_PENALTYBOXLOGIC_H

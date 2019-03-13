//
// Created by aragua on 2019.03.11..
//

#include "PenaltyBoxLogic.h"
#include "Console.h"
#include "StringBuilder.h"
#include "Configuration.h"
#include "Exceptions.h"

PenaltyBoxLogic::PenaltyBoxLogic(const std::string &playerName)
		: playerName(playerName)
{
	if (playerName.empty())
	{
		Throw(ArgumentException("playerName cannot be empty."));
	}
}

PenaltyStates PenaltyBoxLogic::State() const
{
	return penaltyState;
}

void PenaltyBoxLogic::TryGetOutOfBoxOnDemand(size_t rollValue, std::shared_ptr<RollProvider> &rollProvider)
{
	if (PenaltyStates::InPenaltyBox == State())
	{
		StringBuilder sb;
		
		TryGetOutOfBoxInternal(rollValue);
		
		if (PenaltyStates::InPenaltyBox == State())
		{
			sb << playerName << " is not getting out of the penalty box";
			
			CorrectFixedLegacyRandomSequenceOnDemand(rollProvider);
		}
		else
		{
			sb << playerName << " is getting out of the penalty box";
		}
		
		Console::WriteLine(sb.ToString());
	}
}

void PenaltyBoxLogic::SendToBox()
{
	if (PenaltyStates::InPenaltyBox == State())
	{
		Throw(InvalidOperationException("Already in penalty box."));
	}
	
	penaltyState = PenaltyStates::InPenaltyBox;
	
	StringBuilder sb;
	sb << playerName << " was sent to the penalty box";
	Console::WriteLine(sb.ToString());
}

void PenaltyBoxLogic::TryGetOutOfBoxInternal(size_t rollValue)
{
	if (PenaltyStates::FreeToPlay == State())
	{
		Throw(InvalidOperationException("Not in penalty box."));
	}
	
	bool success = rollValue % GetOutOfPenaltyBoxThreshold != 0;
	if (success)
	{
		penaltyState = PenaltyStates::FreeToPlay;
	}
}

void PenaltyBoxLogic::CorrectFixedLegacyRandomSequenceOnDemand(std::shared_ptr<RollProvider> &rollProvider)
{
	// NOTE:
	// It produces the same number of calls to srand() in case of fixed legacy random mode to preserve
	// reproducibility after the fix of bug caused by the 'isGettingOutOfPenaltyBox' state.
	
	bool redundantRollRequired = (RandomMode::FixedLegacy == rollProvider->Random()->Mode());
	if (redundantRollRequired)
	{
		rollProvider->RollNextValue();
	}
}

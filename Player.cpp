//
// Created by aragua on 2019.02.20..
//

#include "Player.h"
#include "Exceptions.h"
#include "Configuration.h"

using namespace std;

Player::Player(const string &name)
		: name(name),
		  penaltyLogic(new PenaltyBoxLogic(name))
{
	if (name.empty())
	{
		Throw(ArgumentException("name cannot be empty."));
	}
}

string Player::Name() const
{
	return name;
}

size_t Player::Gold() const
{
	return gold;
}

void Player::IncrementGold()
{
	gold++;
}

size_t Player::Position() const
{
	return position;
}

void Player::IncrementPosition(size_t value)
{
	VerifyIncrementPositionValue(value);
	
	position += value;
	
	if (position >= MaxPosition)
	{
		position -= MaxPosition;
	}
	
	StringBuilder sb;
	sb << Name() << "'s new location is " << Position();
	Console::WriteLine(sb.ToString());
}

void Player::VerifyIncrementPositionValue(size_t value)
{
	auto outOfRange = (0 == value || value > MaxRollValue);
	if (outOfRange)
	{
		Throw(ArgumentOutOfRangeException("Player::VerifyIncrementPositionValue() got wrong value."));
	}
}

bool Player::CanPlay()
{
	return PenaltyStates::FreeToPlay == PenaltyLogic()->State();
}

std::shared_ptr<PenaltyBoxLogic> Player::PenaltyLogic()
{
	return penaltyLogic;
}

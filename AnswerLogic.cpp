//
// Created by aragua on 2019.02.20..
//

#include "AnswerLogic.h"
#include "Player.h"
#include "Console.h"
#include "StringBuilder.h"
#include "Exceptions.h"
#include "Configuration.h"

using namespace std;

AnswerLogic::AnswerLogic(std::shared_ptr<RandomBase> &random)
		: random(random)
{
	if (nullptr == random)
	{
		Throw(ArgumentNullException("random"));
	}
}

void AnswerLogic::Process(std::shared_ptr<Player> &player)
{
	switch (Evaluate())
	{
		case AnswerType::Correct:
			HandleCorrect(player);
			break;
		
		case AnswerType::Wrong:
			HandleWrong(player);
			break;
		
		default: Throw(InvalidOperationException("Unknown AnswerType."));
	}
}

AnswerType AnswerLogic::Evaluate()
{
	auto wasWrong =
			(WrongAnswerCompareTo == (random->Next() % MaxWrongAnswerValue));
	
	return (wasWrong ?
			AnswerType::Wrong :
			AnswerType::Correct);
}

void AnswerLogic::HandleCorrect(shared_ptr<Player> &player) const
{
	Console::WriteLine("Answer was correct!!!!");
	
	player->IncrementGold();
	
	StringBuilder sb;
	sb << player->Name() << " now has " << player->Gold() << " Gold Coins.";
	Console::WriteLine(sb.ToString());
}

void AnswerLogic::HandleWrong(shared_ptr<Player> &player) const
{
	Console::WriteLine("Question was incorrectly answered");
	player->PenaltyLogic()->SendToBox();
}

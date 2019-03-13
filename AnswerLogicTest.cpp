//
// Created by aragua on 2019.02.20..
//

#include "AnswerLogicTest.h"
#include "AnswerLogic.h"
#include "Player.h"
#include "RandomFactory.h"
#include "Configuration.h"

using namespace std;

AnswerLogicTest::AnswerLogicTest(TestRunner &runner) : TestBase(runner)
{
}

std::string AnswerLogicTest::Name() const
{
	return "AnswerLogicTest";
}

void AnswerLogicTest::OnRun()
{
	Test(EvaluateTest());
	Test(CorrectAnswerTest());
	Test(WrongAnswerTest());
}

void AnswerLogicTest::EvaluateTest()
{
	auto fixedRandom = RandomFactory::Create(RandomMode::FixedLegacy);
	AnswerLogic answerLogic(fixedRandom);
	
	const size_t AnswerCount = 100;
	for (size_t attempt = 0; attempt < AnswerCount; attempt++)
	{
		auto answer = answerLogic.Evaluate();
		
		switch (attempt)
		{
			// Wrong answers
			case 1:
			case 3:
			case 5:
			case 13:
			case 18:
			case 37:
			case 39:
			case 66:
			case 80:
			case 96: AssertAreEqual(AnswerType::Wrong, answer);
				break;
				
				// Correct answers
			default: AssertAreEqual(AnswerType::Correct, answer);
				break;
		}
	}
}

void AnswerLogicTest::CorrectAnswerTest()
{
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	AnswerLogic answerLogic(random);
	shared_ptr<Player> player(new Player("dummy"));
	
	answerLogic.HandleCorrect(player);
	
	AssertAreEqual(1, player->Gold());
	AssertAreEqual(PenaltyStates::FreeToPlay, player->PenaltyLogic()->State());
}

void AnswerLogicTest::WrongAnswerTest()
{
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	AnswerLogic answerLogic(random);
	shared_ptr<Player> player(new Player("dummy"));
	
	answerLogic.HandleWrong(player);
	
	AssertAreEqual(0, player->Gold());
	AssertAreEqual(PenaltyStates::InPenaltyBox, player->PenaltyLogic()->State());
}

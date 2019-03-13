//
// Created by aragua on 2019.02.20..
//

#include "PlayerTest.h"
#include "Configuration.h"
#include "RandomFactory.h"

#define dummyName "DummyPlayer"

PlayerTest::PlayerTest(TestRunner &runner) : TestBase(runner)
{
}


std::string PlayerTest::Name() const
{
	return "PlayerTest";
}

void PlayerTest::OnRun()
{
	Test(NotAcceptEmptyStringTest());
	Test(InitialValuesTest());
	Test(GoldTest());
	Test(PositionTest());
}

void PlayerTest::NotAcceptEmptyStringTest()
{
	AssertThrows(ExceptionType::ArgumentException, [&] { Player player(""); });
}

void PlayerTest::InitialValuesTest()
{
	Player player(dummyName);
	
	AssertAreEqual(dummyName, player.Name());
	AssertAreEqual(0, player.Position());
	AssertAreEqual(0, player.Gold());
	AssertAreEqual(PenaltyStates::FreeToPlay, player.PenaltyLogic()->State());
	AssertAreEqual(true, player.CanPlay());
}

void PlayerTest::GoldTest()
{
	Player player(dummyName);
	
	for (size_t i = 0; i < MinGoldToWin; i++)
	{
		AssertAreEqual(i, player.Gold());
		player.IncrementGold();
		AssertAreEqual(i + 1, player.Gold());
	}
}

void PlayerTest::PositionTest()
{
	Player player(dummyName);
	
	AssertThrows(ExceptionType::ArgumentOutOfRange, [&] { player.IncrementPosition(0); });
	AssertThrows(ExceptionType::ArgumentOutOfRange, [&] { player.IncrementPosition(MaxRollValue + 1); });
	
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	RollProvider rollProvider(random);
	
	auto totalValue = 0;
	for (size_t attempt = 0; attempt < DefaultTestComplexity; attempt++)
	{
		auto rollValue = rollProvider.RollNextValue();
		totalValue += rollValue;
		player.IncrementPosition(rollValue);
		
		auto expectedValue = totalValue % MaxPosition;
		AssertAreEqual(expectedValue, player.Position());
	}
}

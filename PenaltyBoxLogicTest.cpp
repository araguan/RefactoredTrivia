//
// Created by aragua on 2019.03.12..
//

#include "PenaltyBoxLogicTest.h"
#include "PenaltyBoxLogic.h"
#include "RandomFactory.h"
#include "Configuration.h"

PenaltyBoxLogicTest::PenaltyBoxLogicTest(TestRunner &runner)
		: TestBase(runner)
{
}

std::string PenaltyBoxLogicTest::Name() const
{
	return "PenaltyBoxLogicTest";
}

void PenaltyBoxLogicTest::OnRun()
{
	Test(NotAcceptEmptyStringTest());
	Test(PenaltyBoxTest());
}

void PenaltyBoxLogicTest::NotAcceptEmptyStringTest()
{
	AssertThrows(ExceptionType::ArgumentException, [&] { PenaltyBoxLogic logic(""); });
}

void PenaltyBoxLogicTest::PenaltyBoxTest()
{
	PenaltyBoxLogic logic("DummyPlayer");
	AssertAreEqual(PenaltyStates::FreeToPlay, logic.State());
	
	logic.SendToBox();
	AssertAreEqual(PenaltyStates::InPenaltyBox, logic.State());
	
	TestResendIsProhibited(logic);
	
	TestTryOutOfPenaltyBox(logic, PenaltyStates::InPenaltyBox, 0);
	TestTryOutOfPenaltyBox(logic, PenaltyStates::FreeToPlay, 1);
}

void PenaltyBoxLogicTest::TestResendIsProhibited(PenaltyBoxLogic &logic)
{
	AssertThrows(ExceptionType::InvalidOperation, [&] { logic.SendToBox(); });
	AssertAreEqual(PenaltyStates::InPenaltyBox, logic.State());
}

void PenaltyBoxLogicTest::TestTryOutOfPenaltyBox(PenaltyBoxLogic &logic, PenaltyStates expectedResult, size_t rollValue)
{
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	std::shared_ptr<RollProvider> rollProvider(new RollProvider(random));
	
	logic.TryGetOutOfBoxOnDemand(rollValue, rollProvider);
	
	AssertAreEqual(expectedResult, logic.State());
}

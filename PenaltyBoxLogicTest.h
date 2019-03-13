//
// Created by aragua on 2019.03.12..
//

#ifndef C_PENALTYBOXLOGICTEST_H
#define C_PENALTYBOXLOGICTEST_H


#include "TestBase.h"

class PenaltyBoxLogic;

class PenaltyBoxLogicTest : public TestBase
{
public:
	explicit PenaltyBoxLogicTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void NotAcceptEmptyStringTest();
	
	void PenaltyBoxTest();
	
	void TestResendIsProhibited(PenaltyBoxLogic &logic);
	
	void TestTryOutOfPenaltyBox(PenaltyBoxLogic &logic, PenaltyStates expectedResult, size_t rollValue);
};


#endif //C_PENALTYBOXLOGICTEST_H

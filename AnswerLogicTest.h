//
// Created by aragua on 2019.02.20..
//

#ifndef C_ANSWERLOGICTEST_H
#define C_ANSWERLOGICTEST_H


#include "TestBase.h"

class AnswerLogicTest : public TestBase
{
public:
	explicit AnswerLogicTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void EvaluateTest();
	
	void CorrectAnswerTest();
	
	void WrongAnswerTest();
};


#endif //C_ANSWERLOGICTEST_H

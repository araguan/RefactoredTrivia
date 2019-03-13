//
// Created by aragua on 2019.02.20..
//

#ifndef C_QUESTIONPROVIDERTEST_H
#define C_QUESTIONPROVIDERTEST_H


#include "TestBase.h"

class QuestionProviderTest : public TestBase
{
public:
	explicit QuestionProviderTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void NotAcceptZeroTest();
	
	void OverIndexingTest();
};


#endif //C_QUESTIONPROVIDERTEST_H

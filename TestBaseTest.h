//
// Created by aragua on 2019.03.05..
//

#ifndef C_TESTBASETEST_H
#define C_TESTBASETEST_H


#include "TestBase.h"

class TestBaseTest : public TestBase
{
public:
	explicit TestBaseTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void AssertThrowsTest();
	
	void AssertEqualTest();
	
	void AssertThatTest();
	
	void AssertNotNullTest();
	
	void AssertListsAreEqualTest();
	
	void AssertListsAreDifferTest();
	
	void AssertContainsTest();
};


#endif //C_TESTBASETEST_H

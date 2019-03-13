//
// Created by aragua on 2019.02.20..
//

#ifndef C_PLAYERTEST_H
#define C_PLAYERTEST_H

#include "TestBase.h"
#include "Player.h"

class PlayerTest : public TestBase
{
public:
	explicit PlayerTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void NotAcceptEmptyStringTest();
	
	void InitialValuesTest();
	
	void GoldTest();
	
	void PositionTest();
};


#endif //C_PLAYERTEST_H
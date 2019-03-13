//
// Created by aragua on 2019.03.11..
//

#ifndef C_ROLLPROVIDERTEST_H
#define C_ROLLPROVIDERTEST_H


#include "TestBase.h"

class RollProviderTest : public TestBase
{
public:
	explicit RollProviderTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void EntropyTest(const RandomMode &mode);
};


#endif //C_ROLLPROVIDERTEST_H

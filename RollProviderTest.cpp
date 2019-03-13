//
// Created by aragua on 2019.03.11..
//

#include "RollProviderTest.h"
#include "Configuration.h"
#include "RandomFactory.h"
#include "RollProvider.h"

using namespace std;

RollProviderTest::RollProviderTest(TestRunner &runner) : TestBase(runner)
{
}

std::string RollProviderTest::Name() const
{
	return "RollProviderTest";
}

void RollProviderTest::OnRun()
{
	Test(EntropyTest(RandomMode::FixedLegacy));
	Test(EntropyTest(RandomMode::TimeBasedLegacy));
	Test(EntropyTest(RandomMode::MersenneTwister));
}

void RollProviderTest::EntropyTest(const RandomMode &mode)
{
	auto random = RandomFactory::Create(mode);
	RollProvider rollProvider(random);
	
	vector<size_t> numberList = vector<size_t>();
	
	for (size_t i = 0; i < DefaultTestRandomSequenceCount; i++)
	{
		size_t rollValue = rollProvider.RollNextValue();
		AssertThat(rollValue <= MaxRollValue);
		numberList.emplace_back(rollValue);
	}
	
	for (size_t i = 0; i < MaxRollValue; i++)
	{
		size_t expectedValue = i + 1;
		AssertContains(numberList, expectedValue);
	}
}

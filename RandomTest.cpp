//
// Created by aragua on 2019.02.18..
//

#include <exception>
#include <vector>
#include "RandomTest.h"
#include "MersenneTwisterRandom.h"
#include "FixedLegacyRandom.h"
#include "TimeBasedLegacyRandom.h"
#include "Configuration.h"

using namespace std;

RandomTest::RandomTest(TestRunner &runner) : TestBase(runner)
{
}

std::string RandomTest::Name() const
{
	return "RandomTest";
}

void RandomTest::OnRun()
{
	Test(FixedLegacyReproducibilityTest());
	
	Test(ResultsAreDifferTest(RandomMode::FixedLegacy, RandomMode::TimeBasedLegacy));
	Test(ResultsAreDifferTest(RandomMode::FixedLegacy, RandomMode::MersenneTwister));
	Test(ResultsAreDifferTest(RandomMode::TimeBasedLegacy, RandomMode::TimeBasedLegacy));
	Test(ResultsAreDifferTest(RandomMode::TimeBasedLegacy, RandomMode::MersenneTwister));
	Test(ResultsAreDifferTest(RandomMode::MersenneTwister, RandomMode::MersenneTwister));
	
	Test(FactoryThrowsOnUnknownModeTest());
	Test(LegacyRandomsAreMutuallyExclusiveTest());
	Test(SuccessfulCreationTest());
}

void RandomTest::FixedLegacyReproducibilityTest()
{
	auto a = CreateRandomList(RandomMode::FixedLegacy);
	auto b = CreateRandomList(RandomMode::FixedLegacy);
	
	AssertListsAreEqual(a, b);
}

void RandomTest::ResultsAreDifferTest(const RandomMode &firstMode, const RandomMode &secondMode)
{
	auto a = CreateRandomList(firstMode);
	auto b = CreateRandomList(secondMode);
	
	AssertListsAreDiffer(a, b);
}

vector<size_t> RandomTest::CreateRandomList(const RandomMode &mode)
{
	vector<size_t> list;
	auto random = RandomFactory::Create(mode);
	
	for (size_t i = 0; i < DefaultTestRandomSequenceCount; i++)
	{
		list.emplace_back(random->Next());
	}
	
	return list;
}

void RandomTest::FactoryThrowsOnUnknownModeTest()
{
	AssertThrows(ExceptionType::InvalidOperation, [&]
	{
		RandomFactory::Create((RandomMode) -1);
	});
}

void RandomTest::LegacyRandomsAreMutuallyExclusiveTest()
{
	AssertCompatibleModesCanLiveTogether();
	
	AssertIncompatibleModesThrows(RandomMode::FixedLegacy, RandomMode::TimeBasedLegacy);
	AssertIncompatibleModesThrows(RandomMode::TimeBasedLegacy, RandomMode::FixedLegacy);
}

void RandomTest::AssertCompatibleModesCanLiveTogether()
{
	for (size_t attempt = 0; attempt < DefaultTestComplexity; attempt++)
	{
		AssertDoesNotThrow([&]
						   {
							   auto fixedLegacyRandom = RandomFactory::Create(RandomMode::FixedLegacy);
							   auto mersenneTwisterRandom = RandomFactory::Create(RandomMode::MersenneTwister);
						   });
		
		AssertDoesNotThrow([&]
						   {
							   auto timeBasedLegacyRandom = RandomFactory::Create(RandomMode::TimeBasedLegacy);
							   auto mersenneTwisterRandom = RandomFactory::Create(RandomMode::MersenneTwister);
						   });
	}
}

void RandomTest::AssertIncompatibleModesThrows(const RandomMode &firstMode, const RandomMode &secondMode)
{
	AssertThrows(ExceptionType::InvalidOperation, [&]
	{
		auto firstRandom = RandomFactory::Create(firstMode);
		auto secondRandom = RandomFactory::Create(secondMode);
	});
}

void RandomTest::SuccessfulCreationTest()
{
	AssertSuccessfulCreationOf<FixedLegacyRandom>(RandomMode::FixedLegacy);
	AssertSuccessfulCreationOf<TimeBasedLegacyRandom>(RandomMode::TimeBasedLegacy);
	AssertSuccessfulCreationOf<MersenneTwisterRandom>(RandomMode::MersenneTwister);
}
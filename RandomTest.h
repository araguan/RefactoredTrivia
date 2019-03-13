//
// Created by aragua on 2019.02.18..
//

#ifndef C_RANDOMTEST_H
#define C_RANDOMTEST_H

#include "TestBase.h"
#include "Enumerations.h"
#include "RandomFactory.h"
#include "RandomBase.h"

class RandomTest : public TestBase
{
public:
	explicit RandomTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void FixedLegacyReproducibilityTest();
	
	void ResultsAreDifferTest(const RandomMode &firstMode, const RandomMode &secondMode);
	
	void FactoryThrowsOnUnknownModeTest();
	
	void LegacyRandomsAreMutuallyExclusiveTest();
	
	void SuccessfulCreationTest();
	
	void AssertCompatibleModesCanLiveTogether();
	
	void AssertIncompatibleModesThrows(const RandomMode &firstMode, const RandomMode &secondMode);
	
	template<class T>
	void AssertSuccessfulCreationOf(const RandomMode &mode)
	{
		auto random = RandomFactory::Create(mode);
		AssertNotNull(random.get());
		AssertNotNull(dynamic_cast<T *>(random.get()));
		AssertAreEqual(mode, random->Mode());
	}
	
	std::vector<size_t> CreateRandomList(const RandomMode &mode);
};


#endif //C_RANDOMTEST_H

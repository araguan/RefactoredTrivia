//
// Created by aragua on 2019.02.20..
//

#include "QuestionProviderTest.h"
#include "Configuration.h"
#include "QuestionProvider.h"

QuestionProviderTest::QuestionProviderTest(TestRunner &runner) : TestBase(runner)
{
}

std::string QuestionProviderTest::Name() const
{
	return "QuestionProviderTest";
}

void QuestionProviderTest::OnRun()
{
	Test(NotAcceptZeroTest());
	Test(OverIndexingTest());
}

void QuestionProviderTest::NotAcceptZeroTest()
{
	AssertThrows(ExceptionType::ArgumentException, [&] { QuestionProvider(0); });
}

void QuestionProviderTest::OverIndexingTest()
{
	auto size = QuestionCountPerCategory;
	QuestionProvider qm(size);
	
	for (size_t i = 0; i < size; i++)
	{
		AssertDoesNotThrow([&] { qm.Ask(0); });
	}
	
	AssertThrows(ExceptionType::InvalidOperation, [&] { qm.Ask(0); });
}

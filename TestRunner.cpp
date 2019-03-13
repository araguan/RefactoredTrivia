//
// Created by aragua on 2019.02.18..
//

#include "TestRunner.h"
#include "TestBase.h"
#include "RandomTest.h"
#include "AnswerLogicTest.h"
#include "PlayerTest.h"
#include "QuestionProviderTest.h"
#include "PlayerManagerTest.h"
#include "GameTest.h"
#include "TestBaseTest.h"
#include "RollProviderTest.h"
#include "PenaltyBoxLogicTest.h"

using namespace std;

TestRunner::TestRunner()
{
	Init();
}

void TestRunner::Init()
{
	testFixtures.emplace_back(new TestBaseTest(*this));
	testFixtures.emplace_back(new RandomTest(*this));
	testFixtures.emplace_back(new RollProviderTest(*this));
	testFixtures.emplace_back(new AnswerLogicTest(*this));
	testFixtures.emplace_back(new QuestionProviderTest(*this));
	testFixtures.emplace_back(new PenaltyBoxLogicTest(*this));
	testFixtures.emplace_back(new PlayerTest(*this));
	testFixtures.emplace_back(new PlayerManagerTest(*this));
	testFixtures.emplace_back(new GameTest(*this));
}

void TestRunner::RunAll()
{
	for (auto &testClass : testFixtures)
	{
		testClass->Run();
	}
	
	FinalReport();
}

void TestRunner::FinalReport() const
{
	StringBuilder sb;
	sb << ranCount << " test(s) ran, failure(s): " << failureCount;
	
	Console::WriteSeparator();
	Console::WriteLine(sb.ToString());
	Console::WriteSeparator();
}

size_t TestRunner::FailureCount() const
{
	return failureCount;
}

void TestRunner::IncrementFailureCount()
{
	failureCount++;
}

void TestRunner::IncrementRanCount()
{
	ranCount++;
}

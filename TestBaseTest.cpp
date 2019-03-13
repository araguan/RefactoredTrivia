//
// Created by aragua on 2019.03.05..
//

// NOTE & TODO:
// Incomplete, no negative cases are tested yet, so it is much like a
// "characteristics" test. It could be more sophisticated with less
// duplications using virtual methods.
//
// This whole testing thing should be refactored into a separate test library
// with its own specialized "TestBaseTestRunner" or something like that.
// Some metaprogramming could help to make tests more intuitively runnable.
// Macros using __FILE__ & __LINE__ also could be more user friendly.

#include "TestBaseTest.h"

using namespace std;

TestBaseTest::TestBaseTest(TestRunner &runner) : TestBase(runner)
{
}

std::string TestBaseTest::Name() const
{
	return "TestBaseTest";
}

void TestBaseTest::OnRun()
{
	Test(AssertThrowsTest());
	Test(AssertEqualTest());
	Test(AssertThatTest());
	Test(AssertNotNullTest());
	Test(AssertListsAreEqualTest());
	Test(AssertListsAreDifferTest());
	Test(AssertContainsTest());
}

void TestBaseTest::AssertThrowsTest()
{
	auto lastFailureCount = runner.FailureCount();
	
	AssertThrows(ExceptionType::ArgumentNull, [&]
	{
		Throw (ArgumentNullException("Dummy exception."));
	});
	
	AssertAreEqual(lastFailureCount, runner.FailureCount());
}

void TestBaseTest::AssertEqualTest()
{
	auto lastFailureCount = runner.FailureCount();
	{
		AssertAreEqual(0, 0);
		AssertAreEqual(true, true);
		AssertAreEqual(PenaltyStates::InPenaltyBox, PenaltyStates::InPenaltyBox);
	}
	
	AssertAreEqual(lastFailureCount, runner.FailureCount());
}

void TestBaseTest::AssertThatTest()
{
	auto lastFailureCount = runner.FailureCount();
	
	AssertThat(1 > 0);
	AssertThat(1 != 0);
	AssertThat(0 < 1);
	
	std::string s("Árvíztűrő tükörfúrógép");
	AssertThat("Árvíztűrő tükörfúrógép" == s);
	
	AssertAreEqual(lastFailureCount, runner.FailureCount());
}

void TestBaseTest::AssertNotNullTest()
{
	auto lastFailureCount = runner.FailureCount();
	
	AssertNotNull(this);
	
	AssertAreEqual(lastFailureCount, runner.FailureCount());
}

void TestBaseTest::AssertListsAreEqualTest()
{
	vector<size_t> a = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 81};
	vector<size_t> b = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 81};
	
	AssertListsAreEqual(a, b);
}

void TestBaseTest::AssertListsAreDifferTest()
{
	vector<size_t> a = {1, 1, 2, 3, 5, 8};
	vector<size_t> b = {13, 21, 34, 55, 81};
	
	AssertListsAreDiffer(a, b);
	
	vector<size_t> shorter = {1};
	vector<size_t> longer = {1, 1};
	AssertListsAreDiffer(shorter, longer);
}

void TestBaseTest::AssertContainsTest()
{
	vector<size_t> a = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 81};
	
	AssertContains(a, (size_t) 1);
	AssertContains(a, (size_t) 3);
	AssertContains(a, (size_t) 8);
	AssertContains(a, (size_t) 21);
	AssertContains(a, (size_t) 55);
}

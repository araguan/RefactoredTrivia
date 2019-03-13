//
// Created by aragua on 2019.02.18..
//
#include "TestBase.h"

TestBase::TestBase(TestRunner &runner) : runner(runner)
{
}

void TestBase::Run()
{
	ReportProgress();
	
	OnRun();
}

void TestBase::ReportProgress() const
{
	StringBuilder sb;
	sb << "Starting " << Name() << ":";
	
	Console::WriteSeparator();
	Console::WriteLine(sb.ToString());
	Console::WriteSeparator();
}

void TestBase::ReportFailure(const char *fileName, size_t lineNo, const char *expected, const char *given) const
{
	runner.IncrementFailureCount();
	StringBuilder sb;
	sb << "Assertion FAILED: " << fileName << " @ line " << lineNo;
	sb.NewLine() << " Expected " << expected << " but " << given << " was given.";
	
	Console::WriteLine(sb.ToString());
}

void TestBase::AssertDoesNotThrow(std::function<void()> code)
{
	bool caught = false;
	
	try
	{
		code();
	}
	catch (ExceptionBase &ex)
	{
		caught = true;
	}
	
	AssertAreEqual(false, caught);
}

void TestBase::AssertThat(bool condition)
{
	AssertAreEqual(true, condition);
}

void TestBase::AssertNotNull(const void *ptr)
{
	AssertAreEqual(true, nullptr != ptr);
}

bool TestBase::ExceptionTypeMatching(const ExceptionType &expected, const ExceptionType &given) const
{
	return expected == given;
}

const std::string TestBase::NameOf(const ExceptionType &type)
{
	switch (type)
	{
		case ExceptionType::InvalidOperation:
			return "InvalidOperationException";
		case ExceptionType::ArgumentNull:
			return "ArgumentNull";
		case ExceptionType::ArgumentException:
			return "ArgumentException";
		case ExceptionType::ArgumentOutOfRange:
			return "ArgumentOutOfRangeException";
		default: Throw (InvalidOperationException("Unknown ExceptionType"));
	}
}

void TestBase::AssertListsAreEqual(const std::vector<size_t> &a, const std::vector<size_t> &b)
{
	AssertAreEqual(a.size(), b.size());
	
	for (size_t i = 0; i < a.size(); i++)
	{
		AssertAreEqual(a[i], b[i]);
	}
}

void TestBase::AssertListsAreDiffer(const std::vector<size_t> &a, const std::vector<size_t> &b)
{
	AssertThat(0 <= a.size());
	AssertThat(0 <= b.size());
	
	bool listsAreTheSameSize = (a.size() == b.size());
	if (listsAreTheSameSize)
	{
		bool differenceFound = false;
		for (size_t i = 0; i < a.size(); i++)
		{
			bool itemsAreEqual = (a[i] == b[i]);
			if (!itemsAreEqual)
			{
				differenceFound = true;
				break;
			}
		}
		
		AssertThat(differenceFound);
	}
}

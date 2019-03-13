//
// Created by aragua on 2019.02.18..
//

#ifndef C_TESTBASE_H
#define C_TESTBASE_H

#include <vector>
#include <functional>
#include <memory>
#include "TestRunner.h"
#include "Exceptions.h"
#include "StringBuilder.h"
#include "Console.h"

#define Test(testFunc)                                                                  \
{                                                                                       \
    StringBuilder sb;                                                                   \
    sb << "...running test " << #testFunc << "...";                                     \
    Console::WriteLine(sb.ToString());                                                  \
                                                                                        \
    testFunc;                                                                           \
                                                                                        \
    runner.IncrementRanCount();                                                         \
}                                                                                       \

#define AssertAreEqual(expected, given)                                                 \
{                                                                                       \
    if ((expected) != (given))                                                          \
    {                                                                                   \
        ReportFailure(__FILE__, __LINE__, #expected, #given);                           \
    }                                                                                   \
}                                                                                       \


class TestBase
{
public:
	void Run();
	
	virtual ~TestBase() = default;

protected:
	TestRunner &runner;
	
	explicit TestBase(TestRunner &runner);
	
	virtual std::string Name() const = 0;
	
	virtual void OnRun() = 0;
	
	void ReportFailure(const char *fileName, size_t lineNo, const char *expected, const char *given) const;
	
	void AssertThrows(const ExceptionType type, const std::function<void()> &code)
	{
		bool caught = false;
		
		try
		{
			code();
		}
		catch (ExceptionBase &ex)
		{
			StringBuilder sb;
			sb << "Exception (" << NameOf(ex.Type()) << "): " << ex.what();
			Console::WriteLine(sb.ToString());
			
			if (ExceptionTypeMatching(type, ex.Type()))
			{
				caught = true;
			}
		}
		
		AssertThat(caught);
	}
	
	void AssertDoesNotThrow(std::function<void()> code);
	
	void AssertThat(bool condition);
	
	void AssertNotNull(const void *ptr);
	
	void AssertListsAreEqual(const std::vector<size_t> &a, const std::vector<size_t> &b);
	
	void AssertListsAreDiffer(const std::vector<size_t> &a, const std::vector<size_t> &b);
	
	template<typename T>
	void AssertContains(const std::vector<T> &vector, const T &expectedValue)
	{
		bool contains = false;
		for (auto &value : vector)
		{
			if (expectedValue == value)
			{
				contains = true;
				break;
			}
		}
		
		AssertThat(contains);
	}

private:
	void ReportProgress() const;
	
	bool ExceptionTypeMatching(const ExceptionType &expected, const ExceptionType &given) const;
	
	const std::string NameOf(const ExceptionType &type);
};


#endif //C_TESTBASE_H

//
// Created by aragua on 2019.02.18..
//

#ifndef C_TESTRUNNER_H
#define C_TESTRUNNER_H

#include <vector>
#include <memory>

class TestBase;

class TestRunner
{
public:
	TestRunner();
	
	void RunAll();
	
	size_t FailureCount() const;
	
	void IncrementFailureCount();
	
	void IncrementRanCount();

private:
	size_t ranCount = 0;
	size_t failureCount = 0;
	
	std::vector<std::shared_ptr<TestBase>> testFixtures;
	
	void Init();
	
	void FinalReport() const;
};


#endif //C_TESTRUNNER_H

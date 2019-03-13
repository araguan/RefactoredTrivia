//
// Created by aragua on 2019.03.04..
//

#include "Console.h"
#include "TestRunner.h"
#include "GameRunner.h"

void RunTestsOnDemand();

void RunTests();

int main()
{
	GameRunner gameRunner;
	gameRunner.Run();
	
	RunTestsOnDemand();
	
	return 0;
}

void RunTestsOnDemand()
{
	Console::WriteSeparator();
	Console::WriteLine("Do you want to run the tests? (y/n)");
	
	auto key = Console::ReadKey();
	auto shouldRunTests = ('y' == key);
	
	if (shouldRunTests)
	{
		RunTests();
	}
}

void RunTests()
{
	TestRunner runner;
	runner.RunAll();
}

//
// Created by aragua on 2019.02.25..
//

#ifndef C_GAMETEST_H
#define C_GAMETEST_H

#include <memory>
#include "TestBase.h"

class PlayerManager;

class GameTest : public TestBase
{
public:
	explicit GameTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void NoNullPtrAccepted();
	
	void PlayerCountTest();
	
	void StressTest();
	
	void SuccessTest(size_t numQuestionsPerCategory);
	
	void CreateDummyPlayers(std::shared_ptr<PlayerManager> &playerManager, size_t numPlayers) const;
	
	void ReportStressTestProgress(size_t progress) const;
};


#endif //C_GAMETEST_H

//
// Created by aragua on 2019.02.25..
//

#ifndef C_PLAYERMANAGERTEST_H
#define C_PLAYERMANAGERTEST_H


#include "TestBase.h"

class PlayerManager;

class PlayerManagerTest : public TestBase
{
public:
	explicit PlayerManagerTest(TestRunner &runner);

protected:
	std::string Name() const override;
	
	void OnRun() override;

private:
	void NotAcceptEmptyNameTest();
	
	void PlayerManagerTestInitialValuesTest();
	
	void PlayerManagerTestCurrentOnEmptyThrowsTest();
	
	void AddTest();
	
	void HasEnoughPlayersTest();
	
	void SwitchToNextTest();
	
	void WinnerCannotBeNullTest();
	
	void OnlyOneWinnerCanBeSet();
	
	void CreatePlayers(PlayerManager &playerManager, const std::vector<std::string> &names);
	
	void CreatePlayerNames(size_t count, std::vector<std::string> &names);
};


#endif //C_PLAYERMANAGERTEST_H

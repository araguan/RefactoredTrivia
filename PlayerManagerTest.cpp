//
// Created by aragua on 2019.02.25..
//

#include "PlayerManagerTest.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Configuration.h"

using namespace std;

PlayerManagerTest::PlayerManagerTest(TestRunner &runner) : TestBase(runner)
{
}

string PlayerManagerTest::Name() const
{
	return "PlayerManagerTest";
}

void PlayerManagerTest::OnRun()
{
	Test(NotAcceptEmptyNameTest());
	Test(AddTest());
	Test(PlayerManagerTestInitialValuesTest());
	Test(PlayerManagerTestCurrentOnEmptyThrowsTest());
	Test(HasEnoughPlayersTest());
	Test(SwitchToNextTest());
	Test(WinnerCannotBeNullTest());
	Test(OnlyOneWinnerCanBeSet());
}

void PlayerManagerTest::NotAcceptEmptyNameTest()
{
	PlayerManager playerManager;
	
	AssertThrows(ExceptionType::ArgumentException, [&] { playerManager.Add(""); });
}

void PlayerManagerTest::PlayerManagerTestInitialValuesTest()
{
	PlayerManager playerManager;
	
	AssertAreEqual(0, playerManager.Count());
	AssertAreEqual(false, playerManager.HasEnoughPlayers());
}

void PlayerManagerTest::PlayerManagerTestCurrentOnEmptyThrowsTest()
{
	PlayerManager playerManager;
	AssertThrows(ExceptionType::InvalidOperation, [&]
	{
		auto dummyPlayer = playerManager.Current();
	});
	
	playerManager.Add("dummy");
	AssertDoesNotThrow([&] { auto dummyPlayer = playerManager.Current(); });
	AssertNotNull(playerManager.Current().get());
}

void PlayerManagerTest::AddTest()
{
	vector<string> playerNames;
	CreatePlayerNames(DefaultTestComplexity, playerNames);
	
	PlayerManager playerManager;
	
	for (size_t i = 0; i < playerNames.size(); i++)
	{
		auto name = playerNames[i];
		playerManager.Add(name);
		AssertAreEqual(i + 1, playerManager.Count());
	}
}

void PlayerManagerTest::HasEnoughPlayersTest()
{
	PlayerManager playerManager;
	AssertAreEqual(false, playerManager.HasEnoughPlayers());
	
	auto playerCount = MinPlayerCount * DefaultTestComplexity;
	
	vector<string> playerNames;
	CreatePlayerNames(playerCount, playerNames);
	
	// unplayable state
	for (size_t i = 0; i < MinPlayerCount - 1; i++)
	{
		playerManager.Add(playerNames[i]);
		AssertAreEqual(false, playerManager.HasEnoughPlayers());
	}
	
	// first playable state
	auto nameOfFirstPlayerToPass = playerNames[MinPlayerCount - 1];
	playerManager.Add(nameOfFirstPlayerToPass);
	AssertAreEqual(true, playerManager.HasEnoughPlayers());
	
	// still playable state
	for (auto i = MinPlayerCount; i < playerCount; i++)
	{
		playerManager.Add(playerNames[i]);
		AssertAreEqual(true, playerManager.HasEnoughPlayers());
	}
}

void PlayerManagerTest::SwitchToNextTest()
{
	PlayerManager playerManager;
	vector<string> playerNames;
	CreatePlayerNames(DefaultTestComplexity, playerNames);
	CreatePlayers(playerManager, playerNames);
	
	for (size_t attempt = 0; attempt < DefaultTestComplexity; attempt++)
	{
		for (const auto &expectedName : playerNames)
		{
			auto currentPlayer = playerManager.Current();
			
			AssertNotNull(currentPlayer.get());
			AssertThat(expectedName == currentPlayer->Name());
			
			playerManager.SwitchToNext();
		}
	}
}

void PlayerManagerTest::WinnerCannotBeNullTest()
{
	PlayerManager playerManager;
	vector<string> playerNames;
	CreatePlayerNames(DefaultTestComplexity, playerNames);
	CreatePlayers(playerManager, playerNames);
	
	AssertThrows(ExceptionType::ArgumentNull, [&]
	{
		shared_ptr<Player> nullPtr(nullptr);
		playerManager.SetWinner(nullPtr);
	});
}

void PlayerManagerTest::OnlyOneWinnerCanBeSet()
{
	PlayerManager playerManager;
	vector<string> playerNames;
	CreatePlayerNames(DefaultTestComplexity, playerNames);
	CreatePlayers(playerManager, playerNames);
	
	AssertThat(!playerManager.HasWinner());
	
	auto player = playerManager.Current();
	
	AssertDoesNotThrow([&] { playerManager.SetWinner(player); });
	AssertThat(playerManager.HasWinner());
	
	AssertThrows(ExceptionType::InvalidOperation, [&] { playerManager.SetWinner(player); });
	AssertThat(playerManager.HasWinner());
}

void PlayerManagerTest::CreatePlayers(PlayerManager &playerManager, const std::vector<std::string> &names)
{
	for (auto &name : names)
	{
		playerManager.Add(name);
	}
}

void PlayerManagerTest::CreatePlayerNames(size_t count, vector<string> &names)
{
	for (size_t i = 0; i < count; i++)
	{
		auto serialNo = i;
		StringBuilder name;
		name << "Dummy" << serialNo;
		
		names.emplace_back(name.ToString());
	}
}

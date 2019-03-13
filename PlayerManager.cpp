//
// Created by aragua on 2019.02.25..
//

#include "PlayerManager.h"
#include "Console.h"
#include "Player.h"
#include "StringBuilder.h"
#include "Exceptions.h"
#include "Configuration.h"

using namespace std;

void PlayerManager::Add(const string &name)
{
	shared_ptr<Player> player(new Player(name));
	players.emplace_back(player);
	
	StringBuilder sb;
	sb << player->Name() << " was added";
	sb.NewLine() << "They are player number " << Count();
	
	Console::WriteLine(sb.ToString());
}

void PlayerManager::SwitchToNext()
{
	currentPlayerId++;
	
	if (currentPlayerId >= Count())
	{
		currentPlayerId = 0;
	}
}

shared_ptr<Player> PlayerManager::Current()
{
	if (0 == Count())
	{
		Throw(InvalidOperationException("Player count is 0!"));
	}
	
	return players.at(currentPlayerId);
	
}

size_t PlayerManager::Count() const
{
	return players.size();
}

bool PlayerManager::HasEnoughPlayers() const
{
	return (Count() >= MinPlayerCount);
}

void PlayerManager::SetWinner(std::shared_ptr<Player> &player)
{
	if (nullptr == player) Throw(ArgumentNullException("player"));
	if (HasWinner()) Throw(InvalidOperationException("PlayerManager already has winner."));
	
	winner = player;
}

bool PlayerManager::HasWinner() const
{
	return nullptr != winner;
}

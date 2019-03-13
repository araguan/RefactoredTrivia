//
// Created by aragua on 2019.02.25..
//

#ifndef C_PLAYERMANAGER_H
#define C_PLAYERMANAGER_H

#include <memory>
#include <vector>
#include <string>

class Player;

class PlayerManager
{
public:
	void Add(const std::string &name);
	
	size_t Count() const;
	
	void SwitchToNext();
	
	std::shared_ptr<Player> Current();
	
	bool HasEnoughPlayers() const;
	
	void SetWinner(std::shared_ptr<Player> &player);
	
	bool HasWinner() const;

private:
	std::vector<std::shared_ptr<Player>> players;
	std::shared_ptr<Player> winner = nullptr;
	size_t currentPlayerId = 0;
};


#endif //C_PLAYERMANAGER_H

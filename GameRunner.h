//
// Created by aragua on 2019.03.04..
//

#ifndef C_GAMERUNNER_H
#define C_GAMERUNNER_H

#include <memory>
#include "Enumerations.h"
#include "RandomBase.h"

class PlayerManager;

class GameRunner
{
public:
	void Run();

private:
	void CreatePlayers(PlayerManager &playerManager) const;
};

#endif //C_GAMERUNNER_H

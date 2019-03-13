
#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "RollProvider.h"

class Player;

class PlayerManager;

class QuestionProvider;

class AnswerLogic;

class Game
{
public:
	Game(std::shared_ptr<RollProvider> &rollProvider,
		 std::shared_ptr<PlayerManager> &playerManager,
		 std::shared_ptr<QuestionProvider> &questionProvider,
		 std::shared_ptr<AnswerLogic> &answerLogic);
	
	void Run();

private:
	std::shared_ptr<RollProvider> rollProvider;
	std::shared_ptr<PlayerManager> playerManager;
	std::shared_ptr<QuestionProvider> questionProvider;
	std::shared_ptr<AnswerLogic> answerLogic;
	
	void VerifyPlayability();
	
	void ProcessRound(std::shared_ptr<Player> &player);
	
	void LogRoundInfo(const std::shared_ptr<Player> &player, size_t rollValue) const;
	
	bool IsWinner(std::shared_ptr<Player> &player) const;
};

#endif // GAME_H_

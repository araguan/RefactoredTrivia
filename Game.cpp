#include "Game.h"
#include "Exceptions.h"
#include "Player.h"
#include "PlayerManager.h"
#include "AnswerLogic.h"
#include "QuestionProvider.h"
#include "Configuration.h"

using namespace std;

Game::Game(std::shared_ptr<RollProvider> &rollProvider,
		   std::shared_ptr<PlayerManager> &playerManager,
		   std::shared_ptr<QuestionProvider> &questionProvider,
		   std::shared_ptr<AnswerLogic> &answerLogic)
		: rollProvider(rollProvider),
		  playerManager(playerManager),
		  questionProvider(questionProvider),
		  answerLogic(answerLogic)
{
	if (nullptr == rollProvider) Throw (ArgumentNullException("rollProvider"));
	if (nullptr == playerManager) Throw (ArgumentNullException("playerManager"));
	if (nullptr == questionProvider) Throw (ArgumentNullException("questionProvider"));
	if (nullptr == answerLogic) Throw (ArgumentNullException("answerLogic"));
}

void Game::Run()
{
	VerifyPlayability();
	
	while (!playerManager->HasWinner())
	{
		auto player = playerManager->Current();
		
		ProcessRound(player);
		
		if (!playerManager->HasWinner())
		{
			playerManager->SwitchToNext();
		}
	}
}

void Game::VerifyPlayability()
{
	if (!playerManager->HasEnoughPlayers())
	{
		Throw(InvalidOperationException("Not enough players to run the game."));
	}
}

void Game::ProcessRound(shared_ptr<Player> &player)
{
	if (nullptr == player) Throw (ArgumentNullException("player"));
	
	const auto rollValue = rollProvider->RollNextValue();
	
	LogRoundInfo(player, rollValue);
	
	player->PenaltyLogic()->TryGetOutOfBoxOnDemand(rollValue, rollProvider);
	
	if (player->CanPlay())
	{
		player->IncrementPosition(rollValue);
		
		questionProvider->Ask(player->Position());
		
		answerLogic->Process(player);
		
		if (IsWinner(player))
		{
			playerManager->SetWinner(player);
		}
	}
}

void Game::LogRoundInfo(const shared_ptr<Player> &player, size_t rollValue) const
{
	StringBuilder sb;
	
	sb << player->Name() << " is the current player";
	sb.NewLine() << "They have rolled a " << rollValue;
	
	Console::WriteLine(sb.ToString());
}

bool Game::IsWinner(std::shared_ptr<Player> &player) const
{
	return (MinGoldToWin <= player->Gold());
}

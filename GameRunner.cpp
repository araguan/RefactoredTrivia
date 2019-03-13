#include <memory>
#include "GameRunner.h"
#include "Game.h"
#include "PlayerManager.h"
#include "AnswerLogic.h"
#include "QuestionProvider.h"
#include "Configuration.h"
#include "RandomFactory.h"

using namespace std;

void GameRunner::Run()
{
	auto random = RandomFactory::Create(ProductionRandomMode);
	
	shared_ptr<RollProvider> rollProvider(new RollProvider(random));
	shared_ptr<PlayerManager> playerManager(new PlayerManager());
	shared_ptr<QuestionProvider> questionProvider(new QuestionProvider(QuestionCountPerCategory));
	shared_ptr<AnswerLogic> answerLogic(new AnswerLogic(random));
	
	CreatePlayers(*playerManager);
	
	Game game(rollProvider, playerManager, questionProvider, answerLogic);
	game.Run();
}

void GameRunner::CreatePlayers(PlayerManager &playerManager) const
{
	playerManager.Add("Chet");
	playerManager.Add("Pat");
	playerManager.Add("Sue");
}

//
// Created by aragua on 2019.02.25..
//

#include "GameTest.h"
#include "PlayerManager.h"
#include "QuestionProvider.h"
#include "AnswerLogic.h"
#include "Configuration.h"
#include "Game.h"
#include "RandomFactory.h"

using namespace std;

GameTest::GameTest(TestRunner &runner) : TestBase(runner)
{
}

string GameTest::Name() const
{
	return "GameTest";
}

void GameTest::OnRun()
{
	Test(NoNullPtrAccepted());
	Test(PlayerCountTest());
	Test(StressTest());
}

void GameTest::NoNullPtrAccepted()
{
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	
	shared_ptr<RollProvider> rollProvider(new RollProvider(random));
	shared_ptr<PlayerManager> playerManager(new PlayerManager());
	shared_ptr<QuestionProvider> questionProvider(new QuestionProvider(QuestionCountPerCategory));
	shared_ptr<AnswerLogic> answerLogic(new AnswerLogic(random));
	
	AssertThrows(ExceptionType::ArgumentNull, [&]
	{
		shared_ptr<RollProvider> nullPtr(nullptr);
		Game(nullPtr, playerManager, questionProvider, answerLogic);
	});
	
	AssertThrows(ExceptionType::ArgumentNull, [&]
	{
		shared_ptr<PlayerManager> nullPtr(nullptr);
		Game(rollProvider, nullPtr, questionProvider, answerLogic);
	});
	
	AssertThrows(ExceptionType::ArgumentNull, [&]
	{
		shared_ptr<QuestionProvider> nullPtr(nullptr);
		Game(rollProvider, playerManager, nullPtr, answerLogic);
	});
	
	AssertThrows(ExceptionType::ArgumentNull, [&]
	{
		shared_ptr<AnswerLogic> nullPtr(nullptr);
		Game(rollProvider, playerManager, questionProvider, nullPtr);
	});
}

void GameTest::PlayerCountTest()
{
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	
	shared_ptr<RollProvider> rollProvider(new RollProvider(random));
	shared_ptr<PlayerManager> playerManager(new PlayerManager());
	shared_ptr<QuestionProvider> questionProvider(new QuestionProvider(QuestionCountPerCategory));
	shared_ptr<AnswerLogic> answerLogic(new AnswerLogic(random));
	
	Game game(rollProvider, playerManager, questionProvider, answerLogic);
	
	// No player
	AssertThrows(ExceptionType::InvalidOperation, [&] { game.Run(); });
	
	// One player
	playerManager->Add("Dummy1");
	AssertThrows(ExceptionType::InvalidOperation, [&] { game.Run(); });
	
	// Two players
	playerManager->Add("Dummy2");
	AssertDoesNotThrow([&] { game.Run(); });
}

void GameTest::StressTest()
{
	const size_t numQuestionsPerCategory = (StressTestComplexity * StressTestQuestionMultiplier);
	
	AssertDoesNotThrow([&]
					   {
						   for (size_t i = 1; i <= StressTestComplexity; i++)
						   {
							   ReportStressTestProgress(i);
							   SuccessTest(numQuestionsPerCategory);
						   }
					   });
}

void GameTest::SuccessTest(size_t numQuestionsPerCategory)
{
	auto random = RandomFactory::Create(DefaultTestRandomMode);
	
	shared_ptr<RollProvider> rollProvider(new RollProvider(random));
	shared_ptr<PlayerManager> playerManager(new PlayerManager());
	shared_ptr<AnswerLogic> answerLogic(new AnswerLogic(random));
	shared_ptr<QuestionProvider> questionProvider(new QuestionProvider(numQuestionsPerCategory));
	
	Game game(rollProvider, playerManager, questionProvider, answerLogic);
	CreateDummyPlayers(playerManager, StressTestComplexity);
	
	game.Run();
	
	AssertThat(playerManager->HasWinner());
}

void GameTest::ReportStressTestProgress(size_t progress) const
{
	StringBuilder sb;
	sb << "Starting stress test " << progress << ". of " << StressTestComplexity << "...";
	
	Console::WriteSeparator();
	Console::WriteLine(sb.ToString());
	Console::WriteSeparator();
}

void GameTest::CreateDummyPlayers(shared_ptr<PlayerManager> &playerManager, size_t numPlayers) const
{
	for (size_t playerId = 0; playerId < numPlayers; playerId++)
	{
		StringBuilder sb;
		sb << "DummyPlayer" << playerId;
		playerManager->Add(sb.ToString());
	}
}

//
// Created by aragua on 2019.02.20..
//

#ifndef C_ANSWERLOGIC_H
#define C_ANSWERLOGIC_H

#include <memory>
#include "RandomBase.h"
#include "Enumerations.h"

class Player;

class AnswerLogic
{
	friend class AnswerLogicTest;

public:
	explicit AnswerLogic(std::shared_ptr<RandomBase> &random);
	
	void Process(std::shared_ptr<Player> &player);

private:
	std::shared_ptr<RandomBase> random;
	
	AnswerType Evaluate();
	
	void HandleCorrect(std::shared_ptr<Player> &player) const;
	
	void HandleWrong(std::shared_ptr<Player> &player) const;
};


#endif //C_ANSWERLOGIC_H

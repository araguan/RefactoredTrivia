//
// Created by aragua on 2019.02.20..
//

#ifndef C_CONFIGURATION_H
#define C_CONFIGURATION_H

#include "Enumerations.h"

/*****************
Game configuration
*****************/
#define ProductionRandomMode            RandomMode::MersenneTwister
#define QuestionCountPerCategory        (size_t) 50
#define MinPlayerCount                  (size_t) 2
#define MinGoldToWin                    (size_t) 6
#define GetOutOfPenaltyBoxThreshold     (size_t) 2
#define MaxPosition                     (size_t) 12
#define MaxRollValue                    (size_t) 5
#define MaxWrongAnswerValue             (size_t) 9
#define WrongAnswerCompareTo            (size_t) 7

/*****************
Test configuration
*****************/
#define DefaultTestRandomMode			RandomMode::MersenneTwister
#define DefaultTestRandomSequenceCount	(size_t) 64
#define DefaultTestComplexity        	(size_t) 100

#define StressTestComplexity            (size_t) 64
#define StressTestQuestionMultiplier    (size_t) 2

#endif //C_CONFIGURATION_H

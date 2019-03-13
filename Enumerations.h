//
// Created by aragua on 2019.02.20..
//

#ifndef C_ENUMERATIONS_H
#define C_ENUMERATIONS_H

enum class AnswerType
{
	Correct,
	Wrong
};

enum class RandomMode
{
	FixedLegacy,
	TimeBasedLegacy,
	MersenneTwister
};

enum class QuestionCategory
{
	Pop,
	Science,
	Sports,
	Rock
};

enum class PenaltyStates
{
	FreeToPlay,
	InPenaltyBox
};

enum class ExceptionType
{
	InvalidOperation,
	ArgumentNull,
	ArgumentException,
	ArgumentOutOfRange
};

#endif //C_ENUMERATIONS_H

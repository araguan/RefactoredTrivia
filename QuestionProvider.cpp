//
// Created by aragua on 2019.02.20..
//

#include <string>
#include <iostream>
#include "QuestionProvider.h"
#include "Exceptions.h"

using namespace std;

QuestionProvider::QuestionProvider(size_t questionCountPerCategory)
{
	if (0 == questionCountPerCategory)
	{
		Throw(ArgumentException("questionCountPerCategory must exceed zero."));
	}
	
	for (size_t i = 0; i < questionCountPerCategory; i++)
	{
		RegisterQuestion(QuestionCategory::Pop, i);
		RegisterQuestion(QuestionCategory::Science, i);
		RegisterQuestion(QuestionCategory::Sports, i);
		RegisterQuestion(QuestionCategory::Rock, i);
	}
}

void QuestionProvider::RegisterQuestion(QuestionCategory category, size_t index)
{
	RegisterCategoryOnDemand(category);
	
	auto list = ListBy(category);
	
	string question = CreateQuestion(category, index);
	list->emplace_back(question);
}

void QuestionProvider::RegisterCategoryOnDemand(QuestionCategory category)
{
	if (!IsContainsCategory(category))
	{
		map.emplace(category, new QuestionList());
	}
}

bool QuestionProvider::IsContainsCategory(QuestionCategory category) const
{
	for (auto &pair : map)
	{
		if (category == pair.first) return true;
	}
	
	return false;
}

std::string QuestionProvider::CreateQuestion(QuestionCategory category, size_t index) const
{
	StringBuilder sb;
	sb << CategoryToString(category) << " Question " << index;
	return sb.ToString();
}

std::string QuestionProvider::CategoryToString(QuestionCategory category) const
{
	switch (category)
	{
		case QuestionCategory::Pop:
			return "Pop";
		case QuestionCategory::Science:
			return "Science";
		case QuestionCategory::Sports:
			return "Sports";
		case QuestionCategory::Rock:
			return "Rock";
		default: Throw(InvalidOperationException("Unknown QuestionCategory."));
	}
}

std::shared_ptr<QuestionList> QuestionProvider::ListBy(QuestionCategory category) const
{
	return map.at(category);
}

void QuestionProvider::Ask(size_t position) const
{
	auto category = GetCategoryFor(position);
	
	StringBuilder sb;
	sb << "The category is " << CategoryToString(category);
	Console::WriteLine(sb.ToString());
	
	AskFromCategory(category);
}

QuestionCategory QuestionProvider::GetCategoryFor(size_t position) const
{
	// NOTE:
	// It could be more algorithmic with % and + operators,
	// but it seems more readable at this low level of complexity.
	switch (position)
	{
		case 0:
		case 4:
		case 8:
			return QuestionCategory::Pop;
		case 1:
		case 5:
		case 9:
			return QuestionCategory::Science;
		case 2:
		case 6:
		case 10:
			return QuestionCategory::Sports;
		default:
			return QuestionCategory::Rock;
	}
}

void QuestionProvider::AskFromCategory(QuestionCategory category) const
{
	auto list = ListBy(category);
	
	if (list->empty())
	{
		Throw(InvalidOperationException("No question in list!"));
	}
	
	const std::string &question = list->front();
	
	Console::WriteLine(question);
	
	list->remove(question);
}

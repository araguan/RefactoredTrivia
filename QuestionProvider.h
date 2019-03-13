//
// Created by aragua on 2019.02.20..
//

#ifndef C_QUESTIONPROVIDER_H
#define C_QUESTIONPROVIDER_H


#include <map>
#include <memory>

#include "Enumerations.h"
#include "QuestionList.h"

class QuestionProvider
{
public:
	explicit QuestionProvider(size_t questionCountPerCategory);
	
	void Ask(size_t position) const;

private:
	std::map<QuestionCategory, std::shared_ptr<QuestionList>> map;
	
	void RegisterQuestion(QuestionCategory category, size_t index);
	
	std::string CreateQuestion(QuestionCategory category, size_t index) const;
	
	std::shared_ptr<QuestionList> ListBy(QuestionCategory category) const;
	
	void RegisterCategoryOnDemand(QuestionCategory category);
	
	bool IsContainsCategory(QuestionCategory category) const;
	
	QuestionCategory GetCategoryFor(size_t position) const;
	
	std::string CategoryToString(QuestionCategory category) const;
	
	void AskFromCategory(QuestionCategory category) const;
};


#endif //C_QUESTIONPROVIDER_H

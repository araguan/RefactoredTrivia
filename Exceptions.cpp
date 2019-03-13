//
// Created by aragua on 2019.02.20..
//

#include <iostream>
#include "Exceptions.h"

/************
ExceptionBase
*************/
ExceptionBase::ExceptionBase(const std::string &whatMessage)
		: whatMessage(whatMessage)
{
}

ExceptionType ExceptionBase::Type() const
{
	return OnType();
}

const char *ExceptionBase::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT
{
	return whatMessage.c_str();
}

/************************
InvalidOperationException
*************************/
InvalidOperationException::InvalidOperationException(const std::string &message)
		: ExceptionBase(message)
{
}

ExceptionType InvalidOperationException::OnType() const
{
	return ExceptionType::InvalidOperation;
}

/********************
ArgumentNullException
*********************/
ArgumentNullException::ArgumentNullException(const std::string &message)
		: ExceptionBase(message)
{
}

ExceptionType ArgumentNullException::OnType() const
{
	return ExceptionType::ArgumentNull;
}

/****************
ArgumentException
*****************/
ArgumentException::ArgumentException(const std::string &message)
		: ExceptionBase(message)
{
}

ExceptionType ArgumentException::OnType() const
{
	return ExceptionType::ArgumentException;
}

/**************************
ArgumentOutOfRangeException
**************************/
ArgumentOutOfRangeException::ArgumentOutOfRangeException(const std::string &message)
		: ExceptionBase(message)
{
}

ExceptionType ArgumentOutOfRangeException::OnType() const
{
	return ExceptionType::ArgumentOutOfRange;
}

//
// Created by aragua on 2019.02.20..
//

#ifndef C_EXCEPTIONS_H
#define C_EXCEPTIONS_H

#include <string>
#include <exception>
#include "Console.h"
#include "StringBuilder.h"
#include "Enumerations.h"

#define Throw(ex)                                                                       \
{                                                                                       \
    StringBuilder sb;                                                                   \
    sb << #ex << " thrown from " << __FILE__ " @ " <<__LINE__;                          \
    Console::WriteLine(sb.ToString());                                                  \
    throw (ex);                                                                         \
}                                                                                       \


class ExceptionBase : public std::exception
{
public:
	virtual ExceptionType Type() const;
	
	const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;

protected:
	explicit ExceptionBase(const std::string &whatMessage);
	
	virtual ExceptionType OnType() const = 0;

private:
	const std::string whatMessage;
};


class InvalidOperationException : public ExceptionBase
{
public:
	explicit InvalidOperationException(const std::string &message);

protected:
	ExceptionType OnType() const override;
};


class ArgumentNullException : public ExceptionBase
{
public:
	explicit ArgumentNullException(const std::string &message);

protected:
	ExceptionType OnType() const override;
};


class ArgumentException : public ExceptionBase
{
public:
	explicit ArgumentException(const std::string &message);

protected:
	ExceptionType OnType() const override;
};


class ArgumentOutOfRangeException : public ExceptionBase
{
public:
	explicit ArgumentOutOfRangeException(const std::string &message);

protected:
	ExceptionType OnType() const override;
};

#endif //C_EXCEPTIONS_H

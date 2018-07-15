/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#pragma once

#include <sstream>

namespace Calculation
{

class CalculationException : public std::exception
{
public:
    CalculationException(const std::string& message, size_t position)
    {
        std::stringstream str;
        str << "CalculatorException at character " << (position + 1) << ": " << message;
        this->message = str.str();
    }

    virtual const char* what() const noexcept
    {
        return message.c_str();
    }
    virtual ~CalculationException()
    {
    }

private:
    std::string message;
};

class CalculatorException : public CalculationException
{
public:
    CalculatorException(const std::string& message, size_t position) : CalculationException(message, position)
    {
    }
    virtual ~CalculatorException()
    {
    }
};

class LexerException : public CalculationException
{
public:
    LexerException(const std::string& message, size_t position) : CalculationException(message, position)
    {
    }
    virtual ~LexerException()
    {
    }
};
}

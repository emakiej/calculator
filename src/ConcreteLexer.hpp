#pragma once

#include "Token.hpp"

#include "Lexer.hpp"

namespace Calculation
{

const char* const LITERAL_REGEX = "[/+-]?[ \t]*(([1-9][0-9]*)|(0))";

class ConcreteLexer : public Lexer
{
public:
    ConcreteLexer(std::string statement) : buffer(statement)
    {
    }

    virtual ~ConcreteLexer()
    {
    }

    virtual bool hasNextToken() const;

    virtual Token pickNextToken() const;

    virtual Token popNextToken();

    virtual long unsigned int getPosition() const
    {
        return position;
    }

private:
    std::string buffer;
    unsigned long position = 0;

    Token lastPoppedToken = Token();
};
}

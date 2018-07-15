/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#pragma once

#include "Token.hpp"

#include <string>
#include <vector>

namespace Calculation
{

class Lexer
{
public:
    virtual bool hasNextToken() const = 0;
    virtual Token pickNextToken() const = 0;
    virtual Token popNextToken() = 0;
    virtual long unsigned int getPosition() const = 0;

    std::vector<Token> popAllTokens()
    {
        std::vector<Token> tokens;
        while(hasNextToken())
            tokens.push_back(popNextToken());
        return tokens;
    }

    virtual ~Lexer() = default;
};
}

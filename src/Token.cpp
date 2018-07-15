/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/

#include "Token.hpp"

namespace Calculation
{

std::ostream& operator<<(std::ostream& stream, const Token& token)
{
    assert(!token.isEmpty());

    switch(token.getType())
    {
    case TokenType::Bracket:
        stream << token.isOpenBracket() ? "(" : ")";
        break;
    case TokenType::Operator:
        switch(token.getOperator())
        {
        case OP::Plus:
            stream << "+";
            break;
        case OP::Minus:
            stream << "-";
            break;
        case OP::Times:
            stream << "*";
            break;
        case OP::Divide:
            stream << "/";
            break;
        }
        break;
    case TokenType::Literal:
        stream << token.getValue();
        break;
    }
    return stream;
}
}

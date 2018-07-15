/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#pragma once

#include <cassert>
#include <sstream>

#include "BigInteger.hpp"
#include "Exception.hpp"

namespace Calculation
{

enum class TokenType : short
{
    Literal,
    Operator,
    Bracket,
    Empty
};

enum class OP : short
{
    Plus,
    Minus,
    Times,
    Divide
};

enum class Bracket : short
{
    Open,
    Close
};

typedef union SpecialTokenData {

    OP operatorType;
    Bracket bracketType;

    SpecialTokenData()
    {
    }
    SpecialTokenData(OP operatorType) : operatorType(operatorType)
    {
    }
    SpecialTokenData(Bracket bracketType) : bracketType(bracketType)
    {
    }

} SpecialTokenData;

class Token
{
public:
    Token() : type(TokenType::Empty), literal("0"), srcLength(0)
    {
    }
    Token(std::string value) : type(TokenType::Literal), literal(value), srcLength(value.size())
    {
    }
    Token(OP value) : type(TokenType::Operator), value(value), srcLength(1)
    {
    }
    Token(Bracket value) : type(TokenType::Bracket), value(value), srcLength(1)
    {
    }

    TokenType getType() const
    {
        return type;
    }

    bool isEmpty() const
    {
        return type == TokenType::Empty;
    }

    bool isOpenBracket() const
    {
        return type == TokenType::Bracket && value.bracketType == Bracket::Open;
    }

    bool isCloseBracket() const
    {
        return type == TokenType::Bracket && value.bracketType == Bracket::Close;
    }

    bool isOperator() const
    {
        return type == TokenType::Operator;
    }

    bool isLiteral() const
    {
        return type == TokenType::Literal;
    }

    BigInteger getValue() const
    {
        assert(type == TokenType::Literal);
        return literal;
    }

    OP getOperator() const
    {
        assert(type == TokenType::Operator);
        return value.operatorType;
    }

    size_t getSrcTextLength()
    {
        return srcLength;
    }

private:
    TokenType type;
    SpecialTokenData value;
    BigInteger literal;
    size_t srcLength;
};

std::ostream& operator<<(std::ostream& stream, const Token& token);
}

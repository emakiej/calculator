#pragma once

#include <string>

#include "BigInteger.hpp"
#include "Lexer.hpp"

namespace Calculation
{

class Calculator
{
public:
    BigInteger calculate(Lexer& lexer);

private:
    BigInteger calculateExpression(Lexer& lexer, bool bracketExpression);
    BigInteger calculateSingleOperation(OP opType, BigInteger& val1, const BigInteger& val2, const Lexer& lexer);
    BigInteger calculateOperandExpression(Lexer& lexer);
    BigInteger calculatePriorityOperation(Lexer& lexer, OP prevOperator);
    BigInteger calculateBracketExpression(Lexer& lexer);
    static bool isPriorityOperator(const Token& token);
    static void popOpenBracketToken(Lexer& lexer);
    static void popCloseBracketToken(Lexer& lexer);
};
}

#include "Calculator.hpp"

#include <cstdlib>
#include <stdexcept>

#include "Exception.hpp"

using namespace std;
using namespace Calculation;

BigInteger Calculator::calculate(Lexer& lexer)
{
    return calculateExpression(lexer, false);
}

BigInteger Calculator::calculateExpression(Lexer& lexer, bool bracketExpression)
{
    BigInteger leftValue = calculateOperandExpression(lexer);

    while(lexer.hasNextToken() && (!bracketExpression || !lexer.pickNextToken().isCloseBracket()))
    {
        if(!lexer.pickNextToken().isOperator())
            throw CalculatorException("Not an operator", lexer.getPosition());
        OP currentOp = lexer.popNextToken().getOperator();
        BigInteger rightValue = calculatePriorityOperation(lexer, currentOp);
        leftValue = calculateSingleOperation(currentOp, leftValue, rightValue, lexer);
    }
    return leftValue;
}

BigInteger Calculator::calculatePriorityOperation(Lexer& lexer, OP prevOperator)
{
    BigInteger leftValue = calculateOperandExpression(lexer);

    while(lexer.hasNextToken() && (prevOperator == OP::Plus || prevOperator == OP::Minus) && isPriorityOperator(lexer.pickNextToken()))
    {
        OP currentOp = lexer.popNextToken().getOperator();
        BigInteger rightOperand = calculateOperandExpression(lexer);
        leftValue = calculateSingleOperation(currentOp, leftValue, rightOperand, lexer);
    }

    return leftValue;
}

BigInteger Calculator::calculateOperandExpression(Lexer& lexer)
{
    if(!lexer.hasNextToken())
        throw CalculatorException("Missing operand", lexer.getPosition());

    Token token = lexer.pickNextToken();
    if(token.isOpenBracket())
        return calculateBracketExpression(lexer);
    else if(token.isLiteral())
    {
        lexer.popNextToken();
        return token.getValue();
    }
    else
        throw CalculatorException("Incorrect syntax", lexer.getPosition());
}

BigInteger Calculator::calculateBracketExpression(Lexer& lexer)
{
    popOpenBracketToken(lexer);

    BigInteger value = calculateExpression(lexer, true);

    popCloseBracketToken(lexer);

    return value;
}

BigInteger Calculator::calculateSingleOperation(OP opType, BigInteger& val1, const BigInteger& val2, const Lexer& lexer)
{
    switch(opType)
    {
    case OP::Plus:
        return val1 + val2;
    case OP::Minus:
        return val1 - val2;
    case OP::Times:
        return val1 * val2;
    case OP::Divide:
        if(val2 == BigInteger("0"))
            throw CalculatorException("Division by 0!", lexer.getPosition());
        return val1 / val2; // remainder lost
    default:
        assert(true);
    }
}

bool Calculator::isPriorityOperator(const Token& token)
{
    return token.isOperator() && (token.getOperator() == OP::Times || token.getOperator() == OP::Divide);
}

void Calculator::popOpenBracketToken(Lexer& lexer)
{
    Token token = lexer.pickNextToken();
    if(!token.isOpenBracket())
        throw CalculatorException("Missing open bracket at beginning of a bracket expression", lexer.getPosition());

    lexer.popNextToken();
}

void Calculator::popCloseBracketToken(Lexer& lexer)
{
    if(!lexer.hasNextToken())
        throw CalculatorException("Missing closing bracket of a bracket expression", lexer.getPosition());

    lexer.popNextToken();
}

#include "CalculatorTest.hpp"

#include "../src/BigInteger.hpp"
#include "../src/Calculator.hpp"
#include "../src/Exception.hpp"
#include "../src/Token.hpp"
#include "LexerMock.hpp"

TEST_F(CalculatorTest, WhenSingleLiteralToken_ReturnsTheNumber)
{
    LexerMock<> lexer("5");
    ASSERT_EQ(calculator.calculate(lexer), BigInteger("5"));
}

TEST_F(CalculatorTest, WhenSingleAddOperation_ReturnsSum)
{
    LexerMock<> lexer("1", OP::Plus, "2");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("3"));
}

TEST_F(CalculatorTest, WhenSingleSubstractOperation_ReturnsSubstraction)
{
    LexerMock<> lexer("1", OP::Minus, "2");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("-1"));
}

TEST_F(CalculatorTest, WhenSingleTimesOperation_ReturnsMultiplication)
{
    LexerMock<> lexer("-1", OP::Times, "2");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("-2"));
}

TEST_F(CalculatorTest, WhenSingleDividOperation_ReturnsDivision)
{
    LexerMock<> lexer("7", OP::Divide, "3");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("2"));
}

TEST_F(CalculatorTest, WhenMultiplePlusMinusOperations_CalculatesSequentially)
{
    LexerMock<> lexer("7", OP::Plus, "3", OP::Minus, "2", OP::Plus, "-3");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("5"));
}

TEST_F(CalculatorTest, WhenPlusAndThenTimesOperation_CalculatesTimesFirst)
{
    LexerMock<> lexer("7", OP::Plus, "3", OP::Times, "2");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("13"));
}

TEST_F(CalculatorTest, WhenMultiplePriorityOperationsSequentially_CalculatesAllPriorityOperationsFirst)
{
    LexerMock<> lexer("2", OP::Minus, "3", OP::Plus, "1", OP::Times, "7", OP::Divide, "3");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("1"));
}

TEST_F(CalculatorTest, WhenSingleLiteralInBrackets_ReturnsTheLiteral)
{
    LexerMock<> lexer(Bracket::Open, "-5", Bracket::Close);

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("-5"));
}

TEST_F(CalculatorTest, WhenExpressionWithBrackets_CalculatesBracketsFirst)
{
    LexerMock<> lexer("3", OP::Times, Bracket::Open, "-5", OP::Plus, "2", Bracket::Close);

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("-9"));
}

TEST_F(CalculatorTest, WhenOperationsWithTheSamePriorityCalledSequentially_CalculatesFromLeftToRight)
{
    LexerMock<> lexer("4", OP::Times, "5", OP::Divide, "10");

    ASSERT_EQ(calculator.calculate(lexer), BigInteger("2"));
}

TEST_F(CalculatorTest, WhenExpressionWithMissingOperand_ThrowsException)
{
    LexerMock<> lexer("3", OP::Times);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenWrongTokenInsteadOfOperand_ThrowsException)
{
    LexerMockWithoutExpectations lexer("3", OP::Times, OP::Plus);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenMissingClosingBracket_ThrowsException)
{
    LexerMockWithoutExpectations lexer(Bracket::Open, "3", OP::Times, OP::Plus);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenRedundantClosingBracket_ThrowsException)
{
    LexerMockWithoutExpectations lexer(Bracket::Open, "1", OP::Plus, "2", Bracket::Close, Bracket::Close);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenEmptyLexer_ThrowsException)
{
    LexerMock<> lexer;

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenPlusAtTheEnd_ThrowsException)
{
    LexerMock<> lexer("2", OP::Plus, "2", OP::Plus);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenPlusAtTheEndOfBrackets_ThrowsException)
{
    LexerMockWithoutExpectations lexer(Bracket::Open, "2", OP::Plus, "2", OP::Plus, Bracket::Close);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenTwoAdjacentOperators_ThrowsException)
{
    LexerMockWithoutExpectations lexer(Bracket::Open, "2", OP::Plus, OP::Minus, "2", OP::Plus, Bracket::Close);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

TEST_F(CalculatorTest, WhenMissingOperatorBetweenTwoOperands_ThrowsException)
{
    LexerMockWithoutExpectations lexer(Bracket::Open, "2", OP::Plus, "2", Bracket::Open);

    ASSERT_THROW(calculator.calculate(lexer), CalculationException);
}

#include "gtest/gtest.h"

#include <vector>

#include "../src/ConcreteLexer.hpp"

using namespace std;
using namespace Calculation;

TEST(LexerTest, WhenEmptyStatement_HasNextTokenReturnsFalse)
{
    ConcreteLexer lexer("");
    ASSERT_EQ(lexer.hasNextToken(), false);
}

TEST(LexerTest, WhenSinglePositiveNumber_HasNextTokenReturnsTrue)
{
    ConcreteLexer lexer("7");
    ASSERT_EQ(lexer.hasNextToken(), true);
}

TEST(LexerTest, WhenSingleLiteral_PicksALiteralTokenWithProperValue)
{
    ConcreteLexer lexer("-7");
    Token token = lexer.pickNextToken();
    ASSERT_EQ(token.isLiteral(), true);
    ASSERT_EQ(token.getValue(), BigInteger("-7"));
}

TEST(LexerTest, WhenZero_PicksZero)
{
    ConcreteLexer lexer("0");
    Token token = lexer.pickNextToken();
    ASSERT_EQ(token.isLiteral(), true);
    ASSERT_EQ(token.getValue(), BigInteger("0"));
}

TEST(LexerTest, WhenMinusZero_PicksZero)
{
    ConcreteLexer lexer("-0");
    Token token = lexer.pickNextToken();
    ASSERT_EQ(token.isLiteral(), true);
    ASSERT_EQ(token.getValue(), BigInteger("0"));
}

TEST(LexerTest, WhenSingleOpenBracket_PicksOpenBracket)
{
    ConcreteLexer lexer("(");
    Token token = lexer.pickNextToken();
    ASSERT_EQ(token.isOpenBracket(), true);
}

TEST(LexerTest, WhenSingleCloseBracket_PicksCloseBracket)
{
    ConcreteLexer lexer(")");
    Token token = lexer.pickNextToken();
    ASSERT_EQ(token.isCloseBracket(), true);
}

TEST(LexerTest, WhenSinglePositiveLiteralInBrackets_PopsBracketNumberBracket)
{
    ConcreteLexer lexer("(2)");
    vector<Token> tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0].isOpenBracket(), true);
    ASSERT_EQ(tokens[1].isLiteral() && tokens[1].getValue() == BigInteger("2"), true);
    ASSERT_EQ(tokens[2].isCloseBracket(), true);
}

TEST(LexerTest, WhenSingleNumberInBracketsWithWhitespaces_IgnoresWhitespaces)
{
    ConcreteLexer lexer("  (   2    )  ");
    vector<Token> tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0].isOpenBracket(), true);
    ASSERT_EQ(tokens[1].isLiteral() && tokens[1].getValue() == BigInteger("2"), true);
    ASSERT_EQ(tokens[2].isCloseBracket(), true);
}

TEST(LexerTest, WhenSingleOperationInBracketsWithWhitespaces_IgnoresWhitespaces)
{
    ConcreteLexer lexer("  (   2   +   3 )  ");
    vector<Token> tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].isOpenBracket(), true);
    ASSERT_EQ(tokens[1].isLiteral() && tokens[1].getValue() == BigInteger("2"), true);
    ASSERT_EQ(tokens[2].isOperator() && tokens[2].getOperator() == OP::Plus, true);
    ASSERT_EQ(tokens[3].isLiteral() && tokens[3].getValue() == BigInteger("3"), true);
    ASSERT_EQ(tokens[4].isCloseBracket(), true);
}

TEST(LexerTest, WhenMinusAndSpaceAtTheEnd_MinusIsTheLastToken)
{
    ConcreteLexer lexer("2 + 2 - ");
    vector<Token> tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[3].isOperator() && tokens[3].getOperator() == OP::Minus, true);
}

TEST(LexerTest, WhenMinusAndSpaceAtTheEndOfBrackets_MinusAndBracketAreLastTokens)
{
    ConcreteLexer lexer("(2 + 2 - )");
    vector<Token> tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 6);
    ASSERT_EQ(tokens[4].isOperator() && tokens[4].getOperator() == OP::Minus, true);
    ASSERT_EQ(tokens[5].isCloseBracket(), true);
}

TEST(LexerTest, WhenVeryLongNumber_NumberPoppedProperlyAndNoMoreTokens)
{
    ConcreteLexer lexer("123123123123123123123");
    auto tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0].isLiteral(), true);
    ASSERT_EQ(tokens[0].getValue(), BigInteger("123123123123123123123"));
}

TEST(LexerTest, WhenInvalidCharacter_ExceptionThrown)
{
    ConcreteLexer lexer("123 - @77");
    ASSERT_THROW(lexer.popAllTokens(), LexerException);
}

TEST(LexerTest, WhenInvalidLiteral_ExceptionThrown)
{
    ConcreteLexer lexer("--123654");
    ASSERT_THROW(lexer.popAllTokens(), LexerException);
}

TEST(LexerTest, WhenSpaceBetweenSignAndNumber_PopsOneLexem)
{
    ConcreteLexer lexer("  -   3");
    auto tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0].isLiteral(), true);
    ASSERT_EQ(tokens[0].getValue(), BigInteger("-3"));
}

TEST(LexerTest, WhenSpaceBetweenSignAndNumber_PositionAfterPopCorrect)
{
    ConcreteLexer lexer("  +   7");
    auto tokens = lexer.popAllTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0].isLiteral(), true);
    ASSERT_EQ(tokens[0].getValue(), BigInteger("7"));
    ASSERT_EQ(lexer.getPosition(), 7);
}

TEST(LexerTest, WhenPositiveNumberStartsWithZero_ExceptionThrown)
{
    ConcreteLexer lexer("0012");
    ASSERT_THROW(lexer.popAllTokens(), LexerException);
}

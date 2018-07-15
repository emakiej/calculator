/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#pragma once

#include "gmock/gmock.h"

#include <list>
#include <vector>

#include "../src/Lexer.hpp"
#include "../src/Token.hpp"

using namespace ::testing;
using namespace Calculation;

template <bool allTokensToBeProcessed = true>
class LexerMock : public Lexer
{
public:
    template <typename... Args>
    LexerMock(Args&&... args)
    {
        setPickPopExpectations(args...);

        ON_CALL(*this, hasNextToken()).WillByDefault(Invoke([this]() { return !pickNextToken().isEmpty(); }));

        EXPECT_CALL(*this, hasNextToken()).Times(AnyNumber());
        EXPECT_CALL(*this, getPosition()).Times(AnyNumber());
    }

    template <typename... Args>
    void setPickPopExpectations(Args&&... args)
    {
        int mandatoryCallsPerToken = allTokensToBeProcessed ? 1 : 0;

        Sequence seq;

        typedef int for_each[sizeof...(Args)];
        for_each{((void)(setPerTokenExpectations(seq, mandatoryCallsPerToken, std::forward<Args>(args))), 0)...};

        EXPECT_CALL(*this, pickNextToken()).Times(AtLeast(mandatoryCallsPerToken)).InSequence(seq).WillRepeatedly(Return(Token()));
    }

    template <typename T>
    void setPerTokenExpectations(Sequence seq, int mandatoryCallsPerToken, T arg)
    {
        EXPECT_CALL(*this, pickNextToken()).Times(AtLeast(mandatoryCallsPerToken)).InSequence(seq).WillRepeatedly(Return(Token(arg)));

        EXPECT_CALL(*this, popNextToken()).Times(Between(mandatoryCallsPerToken, 1)).InSequence(seq).WillOnce(Return(Token(arg)));
    }

    MOCK_CONST_METHOD0(hasNextToken, bool());
    MOCK_CONST_METHOD0(pickNextToken, Token());
    MOCK_METHOD0(popNextToken, Token());
    MOCK_CONST_METHOD0(getPosition, size_t());
};

typedef LexerMock<false> LexerMockWithoutExpectations;

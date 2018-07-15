/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/

#include "../src/BigInteger.hpp"

#include "gtest/gtest.h"

#include <string>

#include "../src/Exception.hpp"

using namespace Calculation;

TEST(BigIntegerTest, WhenBigIntegerFromRegularPositiveStringRepresentation_ToStringIsEqualToInputStringRepresentation)
{
    ASSERT_EQ(BigInteger("123456").toString(), std::string("123456"));
}

TEST(BigIntegerTest, WhenBigIntegerFromPositiveStringRepresentationWithPlus_ToStringIsEqualToRegularStringRepresentation)
{
    ASSERT_EQ(BigInteger("+123456").toString(), std::string("123456"));
}

TEST(BigIntegerTest, WhenBigIntegerFromNegativeStringRepresentation_ToStringIsEqualToInputStringRepresentation)
{
    ASSERT_EQ(BigInteger("-97531").toString(), std::string("-97531"));
}

TEST(BigIntegerTest, WhenDigitsWithSumSmallerThan10Added_ResultIsOneSummedDigit)
{
    ASSERT_EQ(BigInteger("2") + BigInteger("3"), BigInteger("5"));
}

TEST(BigIntegerTest, WhenDigitsWithSumBiggerThan10Added_ResultIsSumInTwoDigits)
{
    ASSERT_EQ(BigInteger("8") + BigInteger("3"), BigInteger("11"));
}

TEST(BigIntegerTest, WhenMoreDigitsSummed_SumIsCorrect)
{
    BigInteger v1("789");
    BigInteger v2("876");
    ASSERT_EQ(v1 + v2, BigInteger("1665"));
}

TEST(BigIntegerTest, WhenNegativePusPositiveOfSmallerAbs_SumIsNegative)
{
    BigInteger v1("-876");
    BigInteger v2("783");
    ASSERT_EQ(v1 + v2, BigInteger("-93"));
}

TEST(BigIntegerTest, WhenSmallerDigitSubstractedFromBigger_ResultIsOneDigitSubstraction)
{
    BigInteger v1("7");
    BigInteger v2("2");
    ASSERT_EQ(v1 - v2, BigInteger("5"));
}

TEST(BigIntegerTest, WhenBiggerDigitSubstractedFromSmaller_ResultIsNegativeSubstraction)
{
    BigInteger v1("2");
    BigInteger v2("8");
    ASSERT_EQ(v1 - v2, BigInteger("-6"));
}

TEST(BigIntegerTest, WhenOneBiggerDigitSubstracterFromTwoDigitWithLastDigitSmallerAndFirstDigit1_ResultHasOneDigit)
{
    ASSERT_EQ(BigInteger("12") - BigInteger("3"), BigInteger("9"));
}

TEST(BigIntegerTest, WhenOneBiggerDigitSubstracterFromTwoDigitWithLastDigitSmaller_ResultHasSmallerFirstDigit)
{
    BigInteger v1("25");
    BigInteger v2("7");
    ASSERT_EQ(v1 - v2, BigInteger("18"));
}

TEST(BigIntegerTest, WhenLongerNumbersSubstractedSmallerFromBigger_PositiveResultIsCorrect)
{
    BigInteger v1("975");
    BigInteger v2("183");
    ASSERT_EQ(v1 - v2, BigInteger("792"));
}

TEST(BigIntegerTest, WhenLongerNumbersSubstractedBiggerFromSmaller_NegativeResultIsCorrect)
{
    BigInteger v1("295");
    BigInteger v2("317");
    ASSERT_EQ(v1 - v2, BigInteger("-22"));
}

TEST(BigIntegerTest, WhenNegativeSubstractedFromPositive_ResultIsSumOfAbsolutes)
{
    BigInteger v1("12");
    BigInteger v2("-38");
    ASSERT_EQ(v1 - v2, BigInteger("50"));
}

TEST(BigIntegerTest, WhenNegativeMinusSmallerNegative_ResultIsAbsLatterMinusAbsFormer)
{
    ASSERT_EQ(BigInteger("-12") - BigInteger("-38"), BigInteger("26"));
}

TEST(BigIntegerTest, WhenNegativeMinusBiggerNegative_ResultIsNegativeAbsFormerMinusAmsLatter)
{
    ASSERT_EQ(BigInteger("-27") - BigInteger("-19"), BigInteger("-8"));
}

TEST(BigIntegerTest, WhenMultiplicationOfTwoOneDigitNumbers_CorrectOneDigit)
{
    ASSERT_EQ(BigInteger("2") * BigInteger("3"), BigInteger("6"));
}

TEST(BigIntegerTest, WhenMultiplicationOfTwoOneDigitNumbers_CorrectTwoDigits)
{
    ASSERT_EQ(BigInteger("8") * BigInteger("9"), BigInteger("72"));
}

TEST(BigIntegerTest, WhenMultiplicationOfOneDigitAndManyDigitsNumbers_Correct)
{
    ASSERT_EQ(BigInteger("8") * BigInteger("999"), BigInteger("7992"));
}

TEST(BigIntegerTest, WhenMultiplicationOfManyDigitsAndOneDigitNumbers_Correct)
{
    ASSERT_EQ(BigInteger("888888") * BigInteger("7"), BigInteger("6222216"));
}

TEST(BigIntegerTest, WhenMultiplicationOfTwoManyDigitsNumbers_Correct)
{
    ASSERT_EQ(BigInteger("888888") * BigInteger("9999999"), BigInteger("8888879111112"));
}

TEST(BigIntegerTest, WhenMultiplicaionOfNegativeAndPositive_ResultNegative)
{
    ASSERT_EQ(BigInteger("10") * BigInteger("-16"), BigInteger("-160"));
}

TEST(BigIntegerTest, WhenMultiplicaionOfNegativeAndNegative_ResultPositive)
{
    ASSERT_EQ(BigInteger("-153") * BigInteger("-14"), BigInteger("2142"));
}

TEST(BigIntegerTest, WhenDivisionByDivisor_ExactResult)
{
    ASSERT_EQ(BigInteger("144") / BigInteger("12"), BigInteger("12"));
}

TEST(BigIntegerTest, WhenDivisionSmallerByBiggerAbs_ResultIsZero)
{
    ASSERT_EQ(BigInteger("153") / BigInteger("-200"), BigInteger("0"));
}

TEST(BigIntegerTest, WhenDiVisionByNonDivisor_FloorResult)
{
    ASSERT_EQ(BigInteger("150") / BigInteger("-13"), BigInteger("-11"));
}

TEST(BigIntegerTest, WhenDivisionOfPositiveAndNegative_ResultNegative)
{
    ASSERT_EQ(BigInteger("2000000") / BigInteger("-10"), BigInteger("-200000"));
}

TEST(BigIntegerTest, WhenDivisionOfNegativeAndPositive_ResultNegative)
{
    ASSERT_EQ(BigInteger("-150") / BigInteger("13"), BigInteger("-11"));
}

TEST(BigIntegerTest, WhenDivisionOfNegativeAndNegative_ResultPositive)
{
    ASSERT_EQ(BigInteger("-2000000") / BigInteger("-10"), BigInteger("200000"));
}

TEST(BigIntegerTest, WhenVeryLongNumbersMultiplied_ResultCorrect)
{
    ASSERT_EQ(BigInteger("152587890625") * BigInteger("65536"), BigInteger("10000000000000000")); // 5^16 * 2^16 == 10^16
}

TEST(BigIntegerTest, WhenVeryLongNumbersDividedd_ResultCorrect)
{
    ASSERT_EQ(BigInteger("10000000000000000") / BigInteger("152587890625"), BigInteger("65536")); // 10^16 / 5^16 == 2^16
}

TEST(BigIntegerTest, WhenPositiveTimesZero_ResultIsZero)
{
    ASSERT_EQ(BigInteger("152587890625") * BigInteger("0"), BigInteger("0"));
}

TEST(BigIntegerTest, WhenZeroTimesNegative_ResultIsZero)
{
    ASSERT_EQ(BigInteger("0") * BigInteger("-65536"), BigInteger("0"));
}

TEST(BigIntegerTest, Test)
{
    BigInteger v1("122345");
    BigInteger v2 = std::move(v1);
    ASSERT_EQ(v2, BigInteger("122345"));
}

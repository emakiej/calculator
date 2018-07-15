/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#pragma once

#include <string>
#include <vector>

namespace Calculation
{

class BigInteger
{
public:
    BigInteger()
    {
    }

    BigInteger(const std::string& stringRepresentation);

    BigInteger operator+(const BigInteger& other) const;

    BigInteger& operator+=(const BigInteger& other)
    {
        return *this = *this + other;
    }

    BigInteger& operator+=(unsigned char digit)
    {
        return *this = *this + BigInteger(std::string(1, digit + '0'));
    }

    BigInteger operator-(const BigInteger& other) const;

    BigInteger& operator-=(const BigInteger& other)
    {
        return *this = *this - other;
    }

    BigInteger operator*(unsigned char digit) const;

    BigInteger& operator*=(unsigned char digit)
    {
        return *this = *this * digit;
    }

    BigInteger operator*(const BigInteger& other) const;

    BigInteger& operator*=(const BigInteger& other)
    {
        return *this = *this * other;
    }

    BigInteger operator/(const BigInteger& other) const;

    bool operator<(const BigInteger& other) const;

    bool operator==(const BigInteger& other) const;

    std::string toString() const;

private:
    BigInteger& makeOpposite();
    BigInteger abs() const;
    static std::vector<unsigned char> addAbs(const std::vector<unsigned char>& v1, const std::vector<unsigned char>& v2);
    static std::vector<unsigned char> calcAbsDelta(const std::vector<unsigned char>& v1, const std::vector<unsigned char>& v2);
    void normalise();
    void shiftUp(unsigned int offset);

    std::vector<unsigned char> str; // BigInteger is reversed basic_string<unsigned int> plus sign. toString reverses and prints
    short sign = 1;                 //-1 or 1
};

std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
}

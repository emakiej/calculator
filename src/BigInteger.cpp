/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#include "BigInteger.hpp"

#include <algorithm>
#include <cassert>
#include <regex>

#include "Exception.hpp"

using namespace std;

namespace Calculation
{

BigInteger::BigInteger(const string& stringRepresentation) : str(stringRepresentation.size(), 0)
{
    regex intRegex("[/+-]?[ \t]*(([1-9][0-9]*)|(0))");
    assert(regex_match(stringRepresentation, intRegex) > 0);

    transform(stringRepresentation.rbegin(), stringRepresentation.rend(), str.begin(),
              [](char c) { return (c >= '0' && c <= '9') ? c - '0' : 0; });

    sign = stringRepresentation[0] == '-' ? -1 : 1;

    normalise();
}

BigInteger BigInteger::abs() const
{
    BigInteger result;
    result.str = this->str;
    result.sign = 1;
    return result;
}

BigInteger BigInteger::operator+(const BigInteger& other) const
{
    BigInteger result;
    if(this->sign * other.sign > 0)
    {
        result.sign = this->sign;
        result.str = addAbs(this->str, other.str);
    }
    else
    {
        result.sign = this->sign * (this->abs() < other.abs() ? -1 : 1); //!!!!!!
        result.str = calcAbsDelta(this->str, other.str);
    }

    result.normalise();
    return result;
}

vector<unsigned char> BigInteger::addAbs(const vector<unsigned char>& v1, const vector<unsigned char>& v2)
{
    vector<unsigned char> result;

    int rest = 0;
    int i;
    for(i = 0; i < v1.size() && i < v2.size(); i++)
    {
        int sum = v1[i] + v2[i] + rest;
        result.push_back(sum % 10);
        rest = sum / 10;
    }
    for(; i < v1.size(); i++)
    {
        int sum = v1[i] + rest;
        result.push_back(sum % 10);
        rest = sum / 10;
    }
    for(; i < v2.size(); i++)
    {
        int sum = v2[i] + rest;
        result.push_back(sum % 10);
        rest = sum / 10;
    }
    if(rest)
        result.push_back(rest);

    return result;
}

vector<unsigned char> BigInteger::calcAbsDelta(const vector<unsigned char>& v1, const vector<unsigned char>& v2)

{
    vector<unsigned char> result;

    int rest = 0;

    bool reversedOrder = v1.size() < v2.size() || v1.size() == v2.size() && lexicographical_compare(v1.rbegin(), v1.rend(), v2.rbegin(), v2.rend());
    const vector<unsigned char>& bigger = reversedOrder ? v2 : v1;
    const vector<unsigned char>& smaller = reversedOrder ? v1 : v2;

    for(int i = 0; i < bigger.size() || i < smaller.size(); i++)
    {
        int substr;
        if(i < bigger.size() && i < smaller.size())
            substr = bigger[i] - smaller[i] + rest;
        else
            substr = bigger[i] + rest;

        rest = 0;
        if(substr < 0)
        {
            substr += 10;
            rest = -1;
        }

        result.push_back(substr);
    }

    assert(rest == 0);

    return result;
}

BigInteger BigInteger::operator-(const BigInteger& other) const
{
    BigInteger result;

    if(this->sign * other.sign < 0)
    {
        result.sign = this->sign;
        result.str = addAbs(this->str, other.str);
    }
    else
    {
        result.sign = this->sign * (this->abs() < other.abs() ? -1 : 1); //!!!!!!!!
        result.str = calcAbsDelta(this->str, other.str);
    }

    result.normalise();
    return result;
}

BigInteger BigInteger::operator*(unsigned char digit) const
{
    BigInteger result;

    int rest = 0;
    for(int i = 0; i < str.size(); i++)
    {
        int multiply = str[i] * digit + rest;
        result.str.push_back(multiply % 10);
        rest = multiply / 10;
    }
    if(rest > 0)
        result.str.push_back(rest);
    return result;
}

BigInteger BigInteger::operator*(const BigInteger& other) const
{
    BigInteger result;

    for(int i = 0; i < str.size(); i++)
    {
        BigInteger component = other;
        component *= str[i];
        component.shiftUp(i);
        result += component;
    }

    result.sign = this->sign * other.sign;

    result.normalise();

    return result;
}

BigInteger BigInteger::operator/(const BigInteger& other) const
{
    BigInteger result;

    BigInteger divisor = other.abs();
    assert(!(divisor == BigInteger("0")));

    result.str.resize(str.size(), 0);

    BigInteger temp("0");
    for(int i = str.size() - 1; i >= 0; i--)
    {
        temp.shiftUp(1);
        temp += str[i];
        while(!(temp < divisor))
        {
            temp -= divisor;
            result.str[i]++;
        }
    }

    result.sign = this->sign * other.sign;

    result.normalise();
    return result;
}

bool BigInteger::operator<(const BigInteger& other) const
{
    if(sign > 0 && other.sign > 0)
    {
        if(str.size() != other.str.size())
            return str.size() < other.str.size();
        else if(str.size() > other.str.size())
            return false;

        for(int i = str.size() - 1; i >= 0; i--)
            if(str[i] != other.str[i])
                return str[i] < other.str[i];
        return false;
    }
    else if(sign > 0 && other.sign < 0)
    {
        return false;
    }
    else if(sign < 0 && other.sign > 0)
    {
        return true;
    }
    else // if (sign < 0 && other.sign < 0)
    {
        if(str.size() != other.str.size())
            return str.size() > other.str.size();

        for(int i = str.size() - 1; i >= 0; i--)
            if(str[i] != other.str[i])
                return str[i] > other.str[i];
        return false;
    }
}

bool BigInteger::operator==(const BigInteger& other) const
{
    return sign == other.sign && str == other.str;
}

void BigInteger::normalise()
{
    while(str[str.size() - 1] == 0 && str.size() > 1)
        str.pop_back();
    if(str.size() == 1 && str[0] == 0)
        sign = 1;
}

string BigInteger::toString() const
{
    stringstream stream;

    if(sign == -1)
        stream << '-';
    std::string temp;
    for(int i = str.size() - 1; i >= 0; i--)
    {
        if(str[i] != 0 || stream.tellp() > (sign < 0 ? 1 : 0) || i == 0)
            stream << (int)str[i];
    }

    temp = stream.str();
    return temp;
}

void BigInteger::shiftUp(unsigned int offset)
{
    str.resize(str.size() + offset);
    for(int i = str.size() - 1; i >= (int)offset; i--)
        str[i] = str[i - offset];
    for(int i = offset - 1; i >= 0; i--)
        str[i] = 0;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi)
{
    return os << bi.toString();
}
}

#include "ConcreteLexer.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <regex>
#include <string>

#include "Exception.hpp"

using namespace std;
using namespace Calculation;

bool ConcreteLexer::hasNextToken() const
{
    unsigned long pickPosition = buffer.find_first_not_of(" \t", position);

    return pickPosition != string::npos && pickPosition < buffer.size();
}

Token ConcreteLexer::pickNextToken() const
{
    unsigned long pickPosition = buffer.find_first_not_of(" \t", position);
    assert(pickPosition != string::npos);

    switch(buffer[pickPosition])
    {
    case '(':
        return Token(Bracket::Open);
    case ')':
        return Token(Bracket::Close);
    case '*':
        return Token(OP::Times);
    case '/':
        return Token(OP::Divide);
    case '+':
    case '-':
        if(!lastPoppedToken.isEmpty() && !lastPoppedToken.isOpenBracket())
            return Token(buffer[pickPosition] == '+' ? OP::Plus : OP::Minus);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        size_t temp = buffer.find_first_not_of(" +-", pickPosition);
        temp = temp != std::string::npos ? buffer.find_first_not_of(" \t", temp) : std::string::npos;
        int nonDigitPosition = temp != std::string::npos ? buffer.find_first_not_of("0123456789", temp) : std::string::npos;
        std::string literalString =
            buffer.substr(pickPosition, nonDigitPosition != std::string::npos ? nonDigitPosition - pickPosition : std::string::npos);

        std::regex intRegex(LITERAL_REGEX);
        if(std::regex_match(literalString, intRegex) == 0)
            throw LexerException("Not a valid integer value", pickPosition);

        return Token(literalString);
    }
    case '\0':
        return Token();
    default:
        throw LexerException("Unsupported character", getPosition());
    }
}

Token ConcreteLexer::popNextToken()
{
    Token token = pickNextToken();

    position = buffer.find_first_not_of(" \t", position);
    assert(position != string::npos);

    position += token.getSrcTextLength();

    lastPoppedToken = token;

    return token;
}

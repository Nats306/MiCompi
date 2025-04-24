#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <string>
#include <cctype>
#include <regex>

class Lexer {
public:
    Lexer(const std::string& source);
    Token nextToken();
    
private:
    void readChar();
    void skipWhitespace();
    char peekChar() const;
    bool isLetter(char ch) const;
    bool isNumber(char ch) const;
    std::string readIdentifier();
    std::string readNumber();
    
    std::string source;
    size_t currentPos;
    size_t readPosition;
    char currentChar;
};

#endif // LEXER_HPP
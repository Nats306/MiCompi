#include "lenguaje/lexer.hpp"
#include <regex>

Lexer::Lexer(const std::string& source) : 
    source(source), currentPos(0), readPosition(0), currentChar(0) {
    readChar();
}

void Lexer::readChar() {
    if (readPosition >= source.length()) {
        currentChar = 0;
    } else {
        currentChar = source[readPosition];
    }
    currentPos = readPosition;
    readPosition++;
}

void Lexer::skipWhitespace() {
    while (isspace(currentChar)) {
        readChar();
    }
}

char Lexer::peekChar() const {
    if (readPosition >= source.length()) {
        return 0;
    }
    return source[readPosition];
}

bool Lexer::isLetter(char ch) const {
    return std::regex_match(std::string(1, ch), std::regex("^[a-záéíóúA-ZÁÉÍÓÚñÑ_]$"));
}

bool Lexer::isNumber(char ch) const {
    return std::isdigit(ch);
}

std::string Lexer::readIdentifier() {
    size_t startPos = currentPos;
    bool isFirstLetter = true;
    
    while (isLetter(currentChar) || (!isFirstLetter && isNumber(currentChar))) {
        readChar();
        isFirstLetter = false;
    }
    
    return source.substr(startPos, currentPos - startPos);
}

std::string Lexer::readNumber() {
    size_t startPos = currentPos;
    while (isNumber(currentChar)) {
        readChar();
    }
    return source.substr(startPos, currentPos - startPos);
}

std::string Lexer::readNumberDecimal() {
    size_t startPos = currentPos;
    bool tienePunto = false;

    while (isNumber(currentChar) || (!tienePunto && currentChar == '.')) {
        if (currentChar == '.') {
            tienePunto = true;
        }
        readChar();
    }
    return source.substr(startPos, currentPos - startPos);
}

std::string Lexer::readString() {
    size_t startPos = currentPos + 1;
    readChar();

    while (currentChar != '"' && currentChar != 0) {
        readChar();
    }

    std::string str = source.substr(startPos, currentPos - startPos);

    readChar();
    return str;
}


Token Lexer::nextToken() {
    skipWhitespace();
    
    Token token(TokenType::ILLEGAL, std::string(1, currentChar));
    
    switch (currentChar) {
        case '=':
            if (peekChar() == '=') {
                readChar();
                token = Token(TokenType::EQ, "==");
            } else {
                token = Token(TokenType::ASSIGN, "=");
            }
            break;
        case '+':
            token = Token(TokenType::PLUS, "+");
            break;
        case ',':
            token = Token(TokenType::COMMA, ",");
            break;
        case ';':
            token = Token(TokenType::SEMICOLON, ";");
            break;
        case 0:
            token = Token(TokenType::EOF_, "");
            break;
        case '>':
            if (peekChar() == '=') {
                readChar();
                token = Token(TokenType::GTE, ">=");
            } else {
                token = Token(TokenType::GT, ">");
            }
            break;
        case '<':
            if (peekChar() == '=') {
                readChar();
                token = Token(TokenType::LTE, "<=");
            } else {
                token = Token(TokenType::LT, "<");
            }
            break;
        case '!':
            if (peekChar() == '=') {
                readChar();
                token = Token(TokenType::NOE, "!=");
            } else {
                token = Token(TokenType::NOT, "!");
            }
            break;
        case '/':
            token = Token(TokenType::SLASH, "/");
            break;
        case '*':
            token = Token(TokenType::ASTERISK, "*");
            break;
        case '(':
            token = Token(TokenType::LPAREN, "(");
            break;
        case ')':
            token = Token(TokenType::RPAREN, ")");
            break;
        case '{':
            token = Token(TokenType::LBRACE, "{");
            break;
        case '}':
            token = Token(TokenType::RBRACE, "}");
            break;
        case '[':
            token = Token(TokenType::LBRACKET, "[");
            break;
        case ']':
            token = Token(TokenType::RBRACKET, "]");
            break;
        case '-':
            token = Token(TokenType::MINUS, "-");
            break;
        case '"':
            token = Token(TokenType::STRING, readString());
            break;
        default:
            if (isLetter(currentChar)) {
                std::string literal = readIdentifier();
                TokenType type = lookup_token_type(literal);
                return Token(type, literal);
            } else if (isNumber(currentChar)) {
                std::string literal = readNumberDecimal();
                if (literal.find('.') != std::string::npos) {
                    return Token(TokenType::DOUBLE, literal);
                } else {
                    return Token(TokenType::INT, literal);
                }
            }
            break;
    }
    
    readChar();
    return token;
}

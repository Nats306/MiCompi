#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>

enum class TokenType {
    ASSIGN,     // =
    COMMA,      // ,
    DIVISION,
    STRING,
    SEMICOLON,  // ;
    DOUBLE,
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE,     // }
    LBRACKET,   // [
    RBRACKET,   // ]
    ASTERISK,   // *
    SLASH,     // /
    ELSE,
    EOF_,       // EOF (usamos _ porque EOF es una macro en C)
    EQ,         // ==
    FALSE,
    FUNCTION,
    GT,         // >
    GTE,        // >=
    IDENT,      // identificador de variable
    IF,
    ILLEGAL,    // caracteres no válidos
    INT,        // int
    LET,        // Let para asignar variables
    LT,         // <
    LTE,        // <=
    NOE,        // !=
    NOT,        // !
    PLUS,       // +
    MINUS,      // -
    RETURN,
    TRUE
};

struct Token {
    TokenType type;
    std::string literal;
    
    Token(TokenType type, const std::string& literal) : type(type), literal(literal) {}
    
    std::string toString() const {
        static const std::unordered_map<TokenType, std::string> typeNames = {
            {TokenType::ASSIGN, "ASSIGN"}, {TokenType::COMMA, "COMMA"},
            {TokenType::DIVISION, "DIVISION"}, {TokenType::DOUBLE, "DOUBLE"},
            {TokenType::ELSE, "ELSE"}, {TokenType::EOF_, "EOF"},
            {TokenType::EQ, "EQ"}, {TokenType::FALSE, "FALSE"},
            {TokenType::FUNCTION, "FUNCTION"}, {TokenType::GT, "GT"},
            {TokenType::GTE, "GTE"}, {TokenType::IDENT, "IDENT"},
            {TokenType::IF, "IF"}, {TokenType::ILLEGAL, "ILLEGAL"},
            {TokenType::INT, "INT"}, {TokenType::LET, "LET"},
            {TokenType::LT, "LT"}, {TokenType::LTE, "LTE"},
            {TokenType::NOE, "NOE"}, {TokenType::NOT, "NOT"},
            {TokenType::PLUS, "PLUS"}, {TokenType::RETURN, "RETURN"},
            {TokenType::SEMICOLON, "SEMICOLON"}, {TokenType::TRUE, "TRUE"},
            {TokenType::LPAREN, "LPAREN"}, {TokenType::RPAREN, "RPAREN"},
            {TokenType::ASTERISK, "ASTERISK"}, {TokenType::SLASH, "SLASH"},
            {TokenType::LBRACE, "LBRACE"}, {TokenType::RBRACE, "RBRACE"},
            {TokenType::LBRACKET, "LBRACKET"}, {TokenType::RBRACKET, "RBRACKET"},
            {TokenType::MINUS, "MINUS"}, {TokenType::STRING, "STRING"},
        };
        auto it = typeNames.find(type);
        std::string typeStr = (it != typeNames.end()) ? it->second : "UNKNOWN";
        return typeStr + ":" + literal;
    }
    
};

TokenType lookup_token_type(const std::string& literal);

#endif 
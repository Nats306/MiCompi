#include "lenguaje/token.hpp"

#include <unordered_map>

TokenType lookup_token_type(const std::string& literal) {
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"false", TokenType::FALSE},
        {"true", TokenType::TRUE},
        {"function", TokenType::FUNCTION},
        {"return", TokenType::RETURN},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"let", TokenType::LET}
    };
    
    auto it = keywords.find(literal);
    if (it != keywords.end()) {
        return it->second;
    }
    return TokenType::IDENT;
}
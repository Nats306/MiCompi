#include "lenguaje/repl.hpp"
#include "lenguaje/lexer.hpp"
#include "lenguaje/token.hpp"

#include <iostream>
#include <string>


void start_repl() {
    std::cout << "Bienvenido a mi compiladorsito" << std::endl;
    
    std::string source;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, source);
        
        if (source == "end") {
            break;
        }
        
        Lexer lexer(source);
        Token token = lexer.nextToken();
        while (token.type != TokenType::EOF_) {
            std::cout << token.toString() << std::endl;
            token = lexer.nextToken();
        }
    }
}
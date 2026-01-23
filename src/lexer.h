#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

typedef enum{} TokenType;
struct Token{
    TokenType type;
    std::string lexeme;
};

std::vector<Token> lexify(std::string raw_input);


class Scanner{
    public:
        Scanner(std::string source);
        std::vector<Token> scanTokens();
    private:
        void scanToken();
        void addToken();
        void charAt();
        void addVoidToken(TokenType type);
        void addToken(TokenType type, std::string lexeme);
};

#endif

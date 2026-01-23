#include <string>
#include <iostream>
#include <vector>


using namespace std;

typedef enum {
    TEXT,
    SPACE,
    HASH,
    ASTERIX,
    DOUBLE_ASTERIX,
    UNDERSCORE,
    DOUBLE_UNDERSCORE,
    EQN,
    LINK,
    ENOF,
    NLINE,
} TokenType ;

struct Token {
    TokenType type;
    string lexeme;

    Token(TokenType t, std::string lex)
        : type(t), lexeme(lex) {}
};


class Scanner{
    std::string source;
    std::vector<Token> tokens;
    int start;    // start of current lexeme
    int current;  // current char

    public: Scanner(std::string src) : source(src){};

    vector<Token> scanTokens(){
        current = 0;
        while(current < source.length()){
            start = current;

            scanToken();
        }
        tokens.push_back(Token(ENOF, ""));
        return tokens;
    }

    void scanToken(){
        char c = char_at();

        switch (c) {
            case '#':{
                addVoidToken(HASH);
                break;
            };
            case '*':{
                if(match('*')) addVoidToken(DOUBLE_ASTERIX);
                else addVoidToken(ASTERIX);
                break;
            }
            case '_':{
                if(match('_')) addVoidToken(DOUBLE_UNDERSCORE);
                else addVoidToken(UNDERSCORE);
                break;
            }
            case '\n':{
                addVoidToken(NLINE);
                break;
            }
            case ' ' : {
                addVoidToken(SPACE);
                break;
            };
            default: {
                text();
                break;
            }
        }
    }

    bool match(char expected){
        if(current >= source.length()) return false;
        if(source[current] != expected) return false;
        current += 1;
        return true;
    }

    char peek(){
        if(current >= source.length()) return '!';
        return source[current];
    }

    char char_at(){
        return source[current++];
    }

    void addVoidToken(TokenType type){
        tokens.push_back(Token(type, ""));
    }

    void addToken(TokenType type, string lexeme){
        string text = source.substr(start, current);
        tokens.push_back(Token(type, text));
    }

    void text(){
        // keep consuming until we hit a special char
        while(current < source.length() && !isSpecial(peek())){
            char_at();
        }
        string lexeme = source.substr(start, current - start);
        tokens.push_back(Token(TEXT, lexeme));
    }

    bool isSpecial(char c){
        return c == ' ' || c == '#' || c == '*' || c == '_' || c == '\n';
    }


};

vector<Token> lexify(string raw_input){
    Scanner scanner(raw_input);
    vector<Token> tokens = scanner.scanTokens();
    return tokens;
}

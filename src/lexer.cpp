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
    CODE,
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
        while(!isAtEnd()){
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
            // case '\\':{
            //     if(match_escape()) escaped();
            //     else(addCharToken(TEXT));
            //     break;
            // };
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
            case '`':{
                code();
                // else code_double();

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

    bool isAtEnd(){
        return current >= source.length();
    }

    bool match(char expected){
        if(isAtEnd()) return false;
        if(source[current] != expected) return false;
        current += 1;
        return true;
    }

    // bool match_escape(){
    //     if(isAtEnd()) return false;
    //     if(isWhiteSpace(source[current])) return false;
    //     return true;
    // }

    // bool isWhiteSpace(char c){
    //     return (c == ' ') || (c == '\n') || (c == '\t');
    // }

    char peek(){
        if(isAtEnd()) return '!';
        return source[current];
    }

    char char_at(){
        return source[current++];
    }

    // void addCharToken(TokenType type){

    //     if(peek() == '\\'){
    //         cout << "hehe" << "\n";
    //         tokens.push_back(Token(type, string("\\")));
    //         char_at();
    //     }
    //     else tokens.push_back(Token(type, string(1,char_at())));

    //     return;
    // }

    void addVoidToken(TokenType type){
        tokens.push_back(Token(type, ""));
    }

    void text(){
        // keep consuming until we hit a special char
        while(!isAtEnd() && !isSpecial(peek())){
            char_at();
        }
        string lexeme = source.substr(start, current - start);
        tokens.push_back(Token(TEXT, lexeme));
    }

    void code(){
        int recover = current; // this is a bit weird
        while( (peek() != '`' ) && (!isAtEnd())){
            char_at();
        }
        if (isAtEnd()){
            cout << "unclosed code";
            current = recover ; // this is a bit weird
            return;
        }
        string code = source.substr(start + 1, current++ - start - 1  );
        tokens.push_back(Token(CODE, code));
    }


    bool isSpecial(char c){
        return c == ' ' || c == '#' || c == '*' || c == '_' || c == '\n' || c == '`';
    }


};

vector<Token> lexify(string raw_input){
    Scanner scanner(raw_input);
    vector<Token> tokens = scanner.scanTokens();
    return tokens;
}
// to add:
// - ability to escape characters
// - links
// - lists

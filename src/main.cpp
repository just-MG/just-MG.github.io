#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "lexer.h"


using namespace std;
#include <fstream>


const char* TOKEN_NAMES[] = {
    "", " ", "#", "*", "**",
    "_", "__", "EQN", "LINK", "ENOF", "\n"
};


string readFile(const string& filename) {
    ifstream file(filename);
    return string((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
}

int main() {

    string tmp = readFile("../templates/text.txt");
    vector<Token> tokens = lexify(tmp);

    for (const Token& token : tokens) {
        cout  << TOKEN_NAMES[token.type] << token.lexeme ;
    }
}

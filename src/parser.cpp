#include <iostream>
#include <string>
#include "parser.h"

using namespace std;


typedef enum {
    TEXT,
    CTRL_HASH,
    CTRL_AST,
    CTRL_LBRACKET,
    CTRL_RBRACKET,
} TokenType ;



string parseLine(string input){
    string tmp = "Hello World: " + input;

    TokenType a = CTRL_AST;
    cout << a;
    cout << "\n";
    return tmp;

}


// what needs to be supported
/*
 * - headings
 * - bold/italics
 * - links
 * - images
 * - lists
 */
// each md line has its own stack -- unless its a list
// i guess we can parse until ^\n

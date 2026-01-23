#include <iostream>
#include <string>
#include "parser.h"
#include "lexer.h"

using namespace std;





string parseLine(string input){
    string tmp = "Hello World: " + input;

    // parseLine(string input)
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

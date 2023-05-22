#ifndef SOSH_PARSER_H
#define SOSH_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "API/SOSH_Token.h"

class SOSH_Parser { // IST
private:
    std::string value;
    std::vector<SOSH_Token> out;
public:
    std::vector<SOSH_Token> Tokenize(const std::string &s);
    std::vector<SOSH_Token> Tokenize2(const std::string &s);
};

#endif
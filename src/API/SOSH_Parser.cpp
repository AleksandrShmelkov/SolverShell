#include "sshell_api.h"

std::vector<SOSH_Token> SOSH_Parser::Tokenize(const std::string &s){
    size_t start;
    size_t end = 0;
    std::string scut;
    SOSH_Token token;
    out.clear;

    while ((start = s.find_first_not_of(" ", end)) != std::string::npos){
        end = s.find(" ", start);
        token.EditToken(Token_e::SOSH_STRING);
        token.EditValue(s.substr(start, end - start));
        out.push_back(token);
    }

    return out;
};

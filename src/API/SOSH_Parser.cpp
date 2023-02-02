#include "sshell_api.h"

std::vector<SOSH_Token> SOSH_Parser::Tokenize(const std::string &s){
    size_t start;
    size_t end = 0;
    std::string scut;
    SOSH_Token token;
    out.clear();

    while ((start = s.find_first_not_of(" ", end)) != std::string::npos){
        end = s.find(" ", start);
        scut = s.substr(start, end - start);
        if (out.empty() && std::regex_match(scut, std::regex("\\w+"))) { // ^[a-z]
            token.EditToken(Token_e::SOSH_FUNCTION_NAME);
        } else if (std::regex_match(scut, std::regex("^-?(0|[1-9]\\d*)$"))) {
            token.EditToken(Token_e::SOSH_INT);
        } else if (std::regex_match(scut, std::regex("[-+]?\\d*\\.\\d+"))) {
            token.EditToken(Token_e::SOSH_DOUBLE);
        } else if (std::regex_match(scut, std::regex("\\w+"))) {
            token.EditToken(Token_e::SOSH_STRING);
        } else {
            token.EditToken(Token_e::SOSH_UNDEFINED);
        }
        token.EditValue(scut);
        out.push_back(token);
    }

    return out;
};

#include "SOSH_Parser.h"

std::vector<SOSH_Token> SOSH_Parser::Tokenize(const std::string &s){
    size_t start;
    size_t end = 0;
    std::string scut;
    out.clear();

    while ((start = s.find_first_not_of(" ", end)) != std::string::npos){
        end = s.find(" ", start);
        scut = s.substr(start, end - start);
        if (out.empty() && std::regex_match(scut, std::regex("\\w+"))) {
            SOSH_Token tokenout(Token_t::SOSH_FUNCTION_NAME, scut);
            out.push_back(tokenout);
        } else if (std::regex_match(scut, std::regex("^-?(0|[1-9]\\d*)$"))) {
            SOSH_Token tokenout(Token_t::SOSH_INT, scut);
            out.push_back(tokenout);
        } else if (std::regex_match(scut, std::regex("[-+]?\\d*\\.\\d+"))) {
            SOSH_Token tokenout(Token_t::SOSH_DOUBLE, scut);
            out.push_back(tokenout);
        } else if (std::regex_match(scut, std::regex("\\w+"))) {
            SOSH_Token tokenout(Token_t::SOSH_STRING, scut);
            out.push_back(tokenout);
        } else {
            SOSH_Token tokenout(Token_t::SOSH_UNDEFINED, scut);
            out.push_back(tokenout);
        }
    }

    return out;
};

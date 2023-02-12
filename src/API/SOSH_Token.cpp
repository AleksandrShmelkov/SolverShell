#include "sshell_api.h"

/*
void SOSH_Token::EditToken(Token_e t) {
    token = t;
};

void SOSH_Token::EditValue(const std::string &s) {
    value = s;
};

std::string SOSH_Token::TestToken(){
    if (token == Token_e::SOSH_FUNCTION_NAME){
        return "SOSH_FUNCTION_NAME";
    } else if (token == Token_e::SOSH_INT) {
        return "SOSH_INT";
    } else if (token == Token_e::SOSH_DOUBLE) {
        return "SOSH_DOUBLE";
    } else if (token == Token_e::SOSH_STRING) {
        return "SOSH_STRING";
    } else {
        return "SOSH_UNDEFINED";
    }
};

std::string SOSH_Token::TestValue(){
    return value;
};

*/

std::string SOSH_Token::Value(){
    return value;
};

Token_t SOSH_Token::Type(){
    return token;
};

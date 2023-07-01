#include "SOSH_Parser.h"


ASTNode* SOSH_Parser::parse() {
    std::vector<SOSH_Token> tokens = lexer.tokenize();
    return parseExpressionOrFunction(tokens);
};


ASTNode* SOSH_Parser::parseExpressionOrFunction(const std::vector<SOSH_Token>& tokens) {
    const SOSH_Token& token = tokens[currentPosition];
    if (token.GetType() == Token_t::SOSH_FUNCTION_NAME) {
        currentPosition++;
        std::vector<SOSH_Token> arguments;
        arguments.push_back(token); // смотреть метод call в SOSH_Function_Base

        while (currentPosition < tokens.size()) {
            if (tokens[currentPosition].GetType() == Token_t::SOSH_INT || tokens[currentPosition].GetType() == Token_t::SOSH_FLOAT || tokens[currentPosition].GetType() == Token_t::SOSH_DOUBLE) {
                arguments.push_back(tokens[currentPosition]);
            };
            
            if (tokens[currentPosition].GetType() == Token_t::SOSH_OPERATOR && tokens[currentPosition].GetValue<std::string>() == "-") {
                currentPosition++;
                if (currentPosition < tokens.size() && 
                    (tokens[currentPosition].GetType() == Token_t::SOSH_INT 
                    || tokens[currentPosition].GetType() == Token_t::SOSH_FLOAT 
                    || tokens[currentPosition].GetType() == Token_t::SOSH_DOUBLE)) {
                    
                    arguments.push_back(SOSH_Token(tokens[currentPosition].GetType(), "-"+tokens[currentPosition].GetValue<std::string>()));
                };
            };

            if (tokens[currentPosition].GetType() == Token_t::SOSH_STRING) {
                arguments.push_back(tokens[currentPosition]);
            };

            currentPosition++;
        };

        SOSH_Function_Base* shellfind = shell.FindFunction(token.GetValue<std::string>());
        ASTNode* node = new ASTShellFunctionNode(token.GetValue<std::string>(), arguments, shellfind);
        return node;
    } else {
        return parseExpression(tokens);
    };
};

ASTNode* SOSH_Parser::parseExpression(const std::vector<SOSH_Token>& tokens) {
    ASTNode* node = parseTerm(tokens);

    while (currentPosition < tokens.size()) {
        const SOSH_Token& token = tokens[currentPosition];

        if (token.GetType() != Token_t::SOSH_OPERATOR || (token.GetValue<std::string>() != "+" && token.GetValue<std::string>() != "-"))
            break;

        currentPosition++;
        ASTNode* right = parseTerm(tokens);
        node = new BinaryOperatorNode(token.GetValue<std::string>()[0], node, right);
    };

    return node;
};

ASTNode* SOSH_Parser::parseTerm(const std::vector<SOSH_Token>& tokens) {
    ASTNode* node = parseFactor(tokens);

    while (currentPosition < tokens.size()) {
        const SOSH_Token& token = tokens[currentPosition];

        if (token.GetType() != Token_t::SOSH_OPERATOR || (token.GetValue<std::string>() != "*" && token.GetValue<std::string>() != "/"))
            break;

        currentPosition++;
        ASTNode* right = parseFactor(tokens);
        node = new BinaryOperatorNode(token.GetValue<std::string>()[0], node, right);
    };

    return node;
};

ASTNode* SOSH_Parser::parseFactor(const std::vector<SOSH_Token>& tokens) {
    const SOSH_Token& token = tokens[currentPosition];

    if (token.GetType() == Token_t::SOSH_INT || token.GetType() == Token_t::SOSH_FLOAT) {
        currentPosition++;
        return new NumberNode(std::stod(token.GetValue<std::string>()));
    };

    if (token.GetType() == Token_t::SOSH_OPERATOR && token.GetValue<std::string>() == "-") {
        currentPosition++;
        if (currentPosition < tokens.size() && (tokens[currentPosition].GetType() == Token_t::SOSH_INT || tokens[currentPosition].GetType() == Token_t::SOSH_FLOAT)) {
            SOSH_Token numberToken = tokens[currentPosition];
            currentPosition++;
            return new NumberNode(-std::stod(numberToken.GetValue<std::string>()));
        };
        throw std::runtime_error("Invalid expression");
    };

    if (token.GetType() == Token_t::SOSH_DELIMITER && token.GetValue<std::string>() == "(") {
        currentPosition++;
        ASTNode* node = parseExpression(tokens);

        if (currentPosition >= tokens.size() || tokens[currentPosition].GetType() != Token_t::SOSH_DELIMITER || tokens[currentPosition].GetValue<std::string>() != ")") {
            throw std::runtime_error("Mismatched parentheses");
        };

        currentPosition++;
        return node;
    };

    throw std::runtime_error("Invalid expression");
};

std::vector<SOSH_Token> SOSH_Parser::Tokenize(const std::string &s){
    size_t start;
    size_t end = 0;
    std::string scut;
    out.clear();

    while ((start = s.find_first_not_of(" ", end)) != std::string::npos){
        end = s.find(" ", start);
        scut = s.substr(start, end - start);
        if (out.empty() && std::regex_match(scut, std::regex("[А-Яа-я\\w]+"))) {
            SOSH_Token tokenout(Token_t::SOSH_FUNCTION_NAME, scut);
            out.push_back(tokenout);
        } else if (std::regex_match(scut, std::regex("^-?(0|[1-9]\\d*)$"))) {
            SOSH_Token tokenout(Token_t::SOSH_INT, scut);
            out.push_back(tokenout);
        } else if (std::regex_match(scut, std::regex("[-+]?\\d*\\.\\d+"))) {
            SOSH_Token tokenout(Token_t::SOSH_DOUBLE, scut);
            out.push_back(tokenout);
        } else if (std::regex_match(scut, std::regex("[А-Яа-я\\w]+"))) {
            SOSH_Token tokenout(Token_t::SOSH_STRING, scut);
            out.push_back(tokenout);
        } else {
            SOSH_Token tokenout(Token_t::SOSH_UNDEFINED, scut);
            out.push_back(tokenout);
        };
    };

    return out;
};


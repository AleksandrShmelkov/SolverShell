#include "SOSH_Lexer.h"


std::vector<SOSH_Token> Lexer::tokenize() {
    std::vector<SOSH_Token> tokens;
    while (currentPosition < code.length()) {
        if (isWhitespace(code[currentPosition])) {
            currentPosition++;
            continue;
        };

        if (isAlpha(code[currentPosition])) {
            tokens.push_back(parseIdentifierOrKeyword());
            continue;
        };

        if (isDigit(code[currentPosition])) {
            tokens.push_back(parseNumber());
            continue;
        };

        if (code[currentPosition] == '"') {
            tokens.push_back(parseString());
            continue;
        };

        if (code[currentPosition] == '\'') {
            tokens.push_back(parseCharacter());
            continue;
        };

        if (isOperator(code[currentPosition])) {
            tokens.push_back(parseOperator());
            continue;
        };

        if (isDelimiter(code[currentPosition])) {
            tokens.push_back(parseDelimiter());
            continue;
        };

        if (code[currentPosition] == '/' && code[currentPosition + 1] == '/') {
            parseComment();
            continue;
        };

        currentPosition++;
    };

    return tokens;
};

bool Lexer::isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
};

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
};

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
};

bool Lexer::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
            c == '=' || c == '!' || c == '<' || c == '>' || c == '&' ||
            c == '|' || c == '^';
};

bool Lexer::isDelimiter(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' ||
            c == ']' || c == ';' || c == ',';
};

SOSH_Token Lexer::parseIdentifierOrKeyword() {
    std::string lexeme;
    while (currentPosition < code.length() && (isAlpha(code[currentPosition]) || isDigit(code[currentPosition]))) {
        lexeme += code[currentPosition];
        currentPosition++;
    };

    // Проверяем, является ли лексема ключевым словом
    SOSH_Function_Base* shellfind = shell.FindFunction(lexeme);
    Token_t type = Token_t::SOSH_IDENTIFIER;
    if (lexeme == "int") {
        type = Token_t::SOSH_INT;
    } else if (lexeme == "float") {
        type = Token_t::SOSH_FLOAT;
    } else if (lexeme == "double") {
        type = Token_t::SOSH_DOUBLE;
    } else if (lexeme == "string") {
        type = Token_t::SOSH_STRING;
    } else if (lexeme == "char") {
        type = Token_t::SOSH_CHAR;
    } else if (lexeme == "void") {
        type = Token_t::SOSH_VOID;
    } else if (shellfind != nullptr) {
        type = Token_t::SOSH_FUNCTION_NAME;
    };

    return SOSH_Token(type, lexeme);
};

SOSH_Token Lexer::parseNumber() {
    std::string lexeme;
    bool hasDecimal = false;
    bool hasExponent = false;

    while (currentPosition < code.length() && (isDigit(code[currentPosition]) || code[currentPosition] == '.' || code[currentPosition] == 'e' || code[currentPosition] == 'E' || code[currentPosition] == '-' || code[currentPosition] == '+')) {
        lexeme += code[currentPosition];

        if (code[currentPosition] == '.') {
            if (hasDecimal) {
                // Error: Multiple decimal points in a number
                throw std::runtime_error("Multiple decimal points in a number");
            };
            hasDecimal = true;
        } else if (code[currentPosition] == 'e' || code[currentPosition] == 'E') {
            if (hasExponent) {
                // Error: Multiple exponents in a number
                throw std::runtime_error("Multiple exponents in a number");
            };
            hasExponent = true;
        };

        currentPosition++;
    };

    Token_t type = hasDecimal || hasExponent ? Token_t::SOSH_FLOAT : Token_t::SOSH_INT;
    return SOSH_Token(type, lexeme);
};

SOSH_Token Lexer::parseString() {
    std::string lexeme;
    //lexeme += code[currentPosition];  // Add the opening double quote
    currentPosition++;

    while (currentPosition < code.length() && code[currentPosition] != '"') {
        lexeme += code[currentPosition];
        currentPosition++;
    };

    if (currentPosition == code.length() || code[currentPosition] != '"') {
        // Error: Unterminated string
        throw std::runtime_error("Unterminated string");
    };

    //lexeme += code[currentPosition];  // Add the closing double quote
    currentPosition++;

    return SOSH_Token(Token_t::SOSH_STRING, lexeme);
};

SOSH_Token Lexer::parseCharacter() {
    std::string lexeme;
    lexeme += code[currentPosition];  // Add the opening single quote
    currentPosition++;

    if (currentPosition >= code.length()) {
        // Error: Unexpected end of input
        throw std::runtime_error("Unexpected end of input");
    };

    lexeme += code[currentPosition];
    currentPosition++;

    if (currentPosition >= code.length() || code[currentPosition] != '\'') {
        // Error: Missing closing single quote
        throw std::runtime_error("Missing closing single quote");
    };

    lexeme += code[currentPosition];  // Add the closing single quote
    currentPosition++;

    return SOSH_Token(Token_t::SOSH_CHAR, lexeme);
};

SOSH_Token Lexer::parseOperator() {
    std::string lexeme;
    lexeme += code[currentPosition];
    currentPosition++;

    // Check for two-character operators (e.g., ==, <=, >=, !=)
    if (currentPosition < code.length() && (code[currentPosition] == '=' || code[currentPosition] == '!' || code[currentPosition] == '<' || code[currentPosition] == '>')) {
        lexeme += code[currentPosition];
        currentPosition++;
    };

    return SOSH_Token(Token_t::SOSH_OPERATOR, lexeme);
};

SOSH_Token Lexer::parseDelimiter() {
    std::string lexeme;
    lexeme += code[currentPosition];
    currentPosition++;

    return SOSH_Token(Token_t::SOSH_DELIMITER, lexeme);
};

void Lexer::parseComment() {
    while (currentPosition < code.length() && code[currentPosition] != '\n') {
        currentPosition++;
    };
};

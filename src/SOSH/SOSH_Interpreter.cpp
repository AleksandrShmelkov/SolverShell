#include "SOSH_Interpreter.h"

SOSH_Token Interpreter::evaluate(const std::string& expression, SOSH_Shell shell) { 
    SOSH_Parser parser(expression, shell);
    ASTNode* rootNode = parser.parse();
    SOSH_Token result = rootNode->evaluate();
    delete rootNode;
    return result;
}

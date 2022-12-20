#include "sshell_api.h"

int main() {
    SOSH_Functions func;
    SOSH_DeclareFunction("summ", SOSH_Functions& func);
    std::cout << "Get: " << func.get(0) << std::endl;
    return 0;
};

#include "sshell_api.h"

int main() {
    SOSH_Manager Manager;
    Manager.DeclareShell("Shell1");
    SOSH_Shell Shell1 = Manager.FindShell("Shell1");
    Shell1.DeclareFunction("summ");
    std::cout << "Get: " << Shell1.FindFunction("summ").get() << std::endl;
    std::vector<SOSH_Function> list;
    list = Shell1.ListFunction();
    return 0;
};

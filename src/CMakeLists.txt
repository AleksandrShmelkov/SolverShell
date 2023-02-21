set(BINARY ${CMAKE_PROJECT_NAME})
add_executable(${BINARY}_run 
    sshell.cpp 
    API/SOSH_Function.cpp 
    API/SOSH_Function.h 
    API/SOSH_Manager.cpp 
    API/SOSH_Manager.h 
    API/SOSH_Parser.cpp 
    API/SOSH_Parser.h 
    API/SOSH_Shell.cpp 
    API/SOSH_Shell.h 
    API/SOSH_Token.cpp 
    API/SOSH_Token.h 
    API/sshell_api.h)
add_library(${BINARY}_lib STATIC 
    sshell.cpp 
    API/SOSH_Function.cpp 
    API/SOSH_Function.h 
    API/SOSH_Manager.cpp 
    API/SOSH_Manager.h 
    API/SOSH_Parser.cpp 
    API/SOSH_Parser.h 
    API/SOSH_Shell.cpp 
    API/SOSH_Shell.h 
    API/SOSH_Token.cpp 
    API/SOSH_Token.h 
    API/sshell_api.h)

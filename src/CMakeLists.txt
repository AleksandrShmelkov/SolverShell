set(BINARY ${CMAKE_PROJECT_NAME})
add_executable(${BINARY}_run 
    sshell.cpp 
    API/SOSH_Function.cpp 
    API/SOSH_Manager.cpp 
    API/SOSH_Parser.cpp 
    API/SOSH_Shell.cpp 
	API/SOSH_Token.cpp
    API/sshell_api.h)
add_library(${BINARY}_lib STATIC 
    sshell.cpp 
    API/SOSH_Function.cpp 
    API/SOSH_Manager.cpp 
    API/SOSH_Parser.cpp 
    API/SOSH_Shell.cpp 
	API/SOSH_Token.cpp
    API/sshell_api.h)

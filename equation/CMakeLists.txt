set(BINARY ${CMAKE_PROJECT_NAME}_equation)
add_executable(${BINARY} 
    sshell.cpp 
	Equation.cpp 
	Equation.h)
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib)

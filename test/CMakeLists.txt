set(BINARY ${CMAKE_PROJECT_NAME}_test)
add_executable(${BINARY} 
    gtest.cpp
    SOSH_Function_Tests.cpp
    SOSH_Manager_Tests.cpp
    SOSH_Parser_Tests.cpp
    SOSH_Shell_Tests.cpp
    SOSH_Token_Tests.cpp)
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

cmake_minimum_required (VERSION 3.23)

SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin) # ${PROJECT_SOURCE_DIR}/src
message("CIP = ${CMAKE_INSTALL_PREFIX}")
message("CIP = ${CMAKE_CURRENT_LIST_DIR}")

project(SolverShell)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
add_subdirectory(examples/Equation)
add_subdirectory(examples/3DShapeGenerator)

install(TARGETS ${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_SharedLib DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin)

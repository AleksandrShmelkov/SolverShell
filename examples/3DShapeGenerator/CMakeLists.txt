
#set(CMAKE_CXX_FLAGS -Wno-non-pod-varargs)

# Проверка версии CMake
cmake_minimum_required(VERSION 3.5)

# Название проекта и проверка доступности компиляторя с++
project(API)

# Создание библиотек, от которых зависит динамическая библиотека
add_library(random randomization.h randomization.cpp)
add_library(writeinfile writefile.h writefile.cpp)
add_library(shapes shapes.h shapes.cpp)

# Создание динамической библиотеки с именем API
add_library(API SHARED api.cpp)
add_library(Static_lib api.cpp)
add_executable(myAPI main.cpp)

target_link_libraries(shapes
	PRIVATE
		random
)

target_link_libraries(shapes
	PRIVATE
		random
)

target_link_libraries(API
	PRIVATE
		shapes
		writeinfile
)

target_link_libraries(Static_lib
	PRIVATE
		shapes
		writeinfile
)

target_link_libraries(myAPI
	PUBLIC
		Static_lib
)


#  add_library(API SHARED api.cpp randomization.cpp writefile.cpp shapes.cpp)

# SolverShell
set(BINARY ${CMAKE_PROJECT_NAME}_3DShapeGenerator)
add_executable(${BINARY} 
	sosh.cpp
	api.cpp
	api.h
	randomization.cpp
	randomization.h
	shapes.cpp
	shapes.h
	writefile.cpp
	writefile.h)
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib)
# SolverShell end

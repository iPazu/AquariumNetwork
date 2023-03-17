cmake_minimum_required(VERSION 3.16)
project(front)

find_package(SFML 2.5 
COMPONENTS 
system window graphics network audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


file(GLOB SOURCES "*.cpp")
add_executable(front ${SOURCES})

target_link_libraries(front sfml-graphics)
#target_link_libraries(test sfml-window)
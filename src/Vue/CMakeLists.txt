cmake_minimum_required(VERSION 3.16)
project(front)

find_package(SFML 2.5 
COMPONENTS 
system window graphics network audio REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


file(GLOB SOURCES "*.cpp")
add_executable(front ${SOURCES})

target_link_libraries(front Threads::Threads)
target_link_libraries(front sfml-graphics)
#target_link_libraries(test sfml-window)
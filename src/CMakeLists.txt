cmake_minimum_required(VERSION 3.0)
project(Aquarium_Network)
set(CMAKE_CXX_STANDARD 11)


add_subdirectory(Model)
add_subdirectory(Controller)


add_executable(Aquarium_Network main.c main.c)

target_link_libraries(Aquarium_Network pthread)

target_link_libraries(Aquarium_Network model controller)


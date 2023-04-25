cmake_minimum_required(VERSION 3.0)
project(Aquarium_Network)
set(CMAKE_CXX_STANDARD 11)


add_subdirectory(Modele)
add_subdirectory(Controler)


add_executable(Aquarium_Network main.c)

target_link_libraries(Aquarium_Network pthread)

target_link_libraries(Aquarium_Network modele controler)


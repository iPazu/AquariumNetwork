#!/bin/bash

# Compilation des tests
gcc -o test_move check_move.c ../src/Modele/fish.c ../src/Modele/move.c -lcheck
gcc -o test_fish check_fish.c ../src/Modele/fish.c ../src/Modele/move.c -lcheck
gcc -o test_aquarium check_aquarium.c ../src/Modele/fish.c ../src/Modele/move.c ../src/Modele/aquarium.c ../src/Modele/view.c -lcheck

# Exécution des tests
./test_move
./test_fish
./test_aquarium

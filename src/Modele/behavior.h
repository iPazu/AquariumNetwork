//
// Created by Axel PETIT on 18/04/2023.
//

#ifndef AQUARIUM_NETWORK_BEHAVIOR_H
#define AQUARIUM_NETWORK_BEHAVIOR_H

#include "fish.h"

fish* classic_reproduction(fish * f1, fish * f2);

fish * no_hunting(fish *f1, fish *f2);

fish* classic_hunting(fish *f1, fish *f2);

fish *predator_hunting(fish *f1, fish *f2);

#endif //AQUARIUM_NETWORK_BEHAVIOR_H

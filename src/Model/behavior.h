#ifndef AQUARIUM_NETWORK_BEHAVIOR_H
#define AQUARIUM_NETWORK_BEHAVIOR_H

#include "fish.h"

fish* classic_reproduction(fish * f1, fish * f2);

fish * no_hunting(__attribute__((unused)) fish *f1, __attribute__((unused)) fish *f2);

fish* classic_hunting(fish *f1, fish *f2);

fish *predator_hunting(fish *f1, fish *f2);

#endif //AQUARIUM_NETWORK_BEHAVIOR_H

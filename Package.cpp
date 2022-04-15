//
// Created by Rui on 30/03/2022.
//

#include "Package.h"

Package::Package(unsigned volume, unsigned weight, unsigned reward, unsigned int estimatedTime)
        : volume(volume), weight(weight), reward(reward),
          estimatedTime(estimatedTime) {}

unsigned int Package::getVolume() const {
    return volume;
}

unsigned int Package::getWeight() const {
    return weight;
}

unsigned int Package::getReward() const {
    return reward;
}

unsigned int Package::getEstimatedTime() const {
    return estimatedTime;
}

void Package::setAdded() {
    added = true;
}

bool Package::isAlreadyAdded() const {
    return added;
}

void Package::restart() {
    added = false;
}
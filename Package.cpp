//
// Created by Rui on 30/03/2022.
//

#include "Package.h"

Package::Package(unsigned volume, unsigned weight, unsigned reward, unsigned int estimatedTime, unsigned day)
        : volume(volume), weight(weight), reward(reward),
          estimatedTime(estimatedTime), day(day) {}

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

unsigned int Package::getDay() const {
    return day;
}

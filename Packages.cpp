//
// Created by Rui on 30/03/2022.
//

#include "Packages.h"

unsigned int Packages::getVolume() const {
    return volume;
}

void Packages::setVolume(unsigned int volume) {
    Packages::volume = volume;
}

unsigned int Packages::getWeight() const {
    return weight;
}

void Packages::setWeight(unsigned int weight) {
    Packages::weight = weight;
}

unsigned int Packages::getReward() const {
    return reward;
}

void Packages::setReward(unsigned int reward) {
    Packages::reward = reward;
}

unsigned int Packages::getDuration() const {
    return duration;
}

void Packages::setDuration(unsigned int duration) {
    Packages::duration = duration;
}

bool Packages::isExpressDelivery() const {
    return ExpressDelivery;
}

void Packages::setExpressDelivery(bool expressDelivery) {
    ExpressDelivery = expressDelivery;
}

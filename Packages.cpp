//
// Created by Rui on 30/03/2022.
//

#include "Packages.h"

int Packages::getVolume() const {
    return volume;
}

void Packages::setVolume(int volume) {
    Packages::volume = volume;
}

int Packages::getWeight() const {
    return weight;
}

void Packages::setWeight(int weight) {
    Packages::weight = weight;
}

int Packages::getReward() const {
    return reward;
}

void Packages::setReward(int reward) {
    Packages::reward = reward;
}

int Packages::getDuration() const {
    return duration;
}

void Packages::setDuration(int duration) {
    Packages::duration = duration;
}

bool Packages::isExpressDelivery() const {
    return ExpressDelivery;
}

void Packages::setExpressDelivery(bool expressDelivery) {
    ExpressDelivery = expressDelivery;
}

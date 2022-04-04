//
// Created by Rui on 30/03/2022.
//

#include "Packages.h"

Packages::Packages(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int duration) : volume(volume), weight(weight), reward(reward), duration(duration) {}

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
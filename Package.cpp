//
// Created by Rui on 30/03/2022.
//

#include "Package.h"

Package::Package(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int estimatedTime, bool expressDelivery)
: volume(volume), weight(weight), reward(reward),
estimatedTime(estimatedTime), expressDelivery(expressDelivery) {}

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

bool Package::isExpressDelivery() const {
    return expressDelivery;
}

void Package::setAdded() {
    added = true;
}

bool Package::isAlreadyAdded() const {
    return added;
}

void Package::restart() {
    added = false;
    expressDelivery = false;
}

ostream &Package::operator<<(ostream &os) const {
    os << volume << "  " << weight << "  " << reward << "  " << estimatedTime << endl;
    return os;
}

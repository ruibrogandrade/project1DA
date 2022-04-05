//
// Created by gdrp7 on 30/03/2022.
//

#include "Transport.h"

Transport::Transport(unsigned int price, unsigned int maxVol, unsigned int maxWeight, bool expressDelivery)
        : maxVol(maxVol), maxWeight(maxWeight), price(price),
        remainingVolume(maxVol), remainingWeight(maxWeight),
        expressDelivery(expressDelivery){}

unsigned int Transport::getMaxVol() const {
    return maxVol;
}

unsigned int Transport::getMaxWeight() const {
    return maxWeight;
}

unsigned int Transport::getPrice() const {
    return price;
}

const vector<Package> &Transport::getCarriedPackages() const {
    return carriedPackages;
}

unsigned int Transport::getRemainingVolume() {
    return remainingVolume;
}

unsigned int Transport::getRemainingWeight() {
    return remainingWeight;
}

bool Transport::addPackage(Package &package) {
    if (package.getVolume() > remainingVolume || package.getWeight() > remainingWeight)
        return false;

    carriedPackages.push_back(package);
    remainingVolume -= package.getVolume();
    remainingWeight -= package.getWeight();
    return true;
}

void Transport::emptyTransport() {
    carriedPackages.clear();
}

bool Transport::isExpressDelivery() const {
    return expressDelivery;
}

ostream &Transport::operator<<(ostream &os) {
    os << maxVol << "  " << maxWeight << "  " << price << endl;
    return os;
}


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

unsigned int Transport::getRemainingVolume() const {
    return remainingVolume;
}

unsigned int Transport::getRemainingWeight() const {
    return remainingWeight;
}

bool Transport::addPackage(Package &package) {
    if (package.getVolume() > remainingVolume || package.getWeight() > remainingWeight || package.isAlreadyAdded())
        return false;

    carriedPackages.push_back(package);
    package.setAdded();
    remainingVolume -= package.getVolume();
    remainingWeight -= package.getWeight();
    return true;
}

void Transport::restart() {
    carriedPackages.clear();
    expressDelivery = false;
}

bool Transport::isExpressDelivery() const {
    return expressDelivery;
}

int Transport::calculateProfit() {
    profit = 0;
    if(carriedPackages.empty())
        return profit;

    unsigned int totalReward = 0;
    for(auto package : carriedPackages)
        totalReward += package.getReward();

    profit = (int)totalReward - (int)price;
    return profit;
}



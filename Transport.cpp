//
// Created by gdrp7 on 30/03/2022.
//

#include "Transport.h"

Transport::Transport(unsigned price, unsigned maxVol, unsigned maxWeight)
        : maxVol(maxVol), maxWeight(maxWeight), price(price),
          remainingVolume(maxVol), remainingWeight(maxWeight),
          profit(0) {}

unsigned Transport::getMaxVol() const {
    return maxVol;
}

unsigned Transport::getMaxWeight() const {
    return maxWeight;
}

unsigned Transport::getPrice() const {
    return price;
}

int Transport::getProfit() const {
    if (carriedPackages.empty()) return 0;
    return profit;
}

unsigned Transport::getRemainingTime() const {
    return remainingTime;
}

const vector<Package> &Transport::getCarriedPackages() const {
    return carriedPackages;
}

bool Transport::addPackage(Package &package) {
    if (package.getVolume() > remainingVolume || package.getWeight() > remainingWeight || package.isAlreadyAdded())
        return false;

    carriedPackages.push_back(package);
    package.setAdded();
    remainingVolume -= package.getVolume();
    remainingWeight -= package.getWeight();
    profit += (int) package.getReward();
    return true;
}

bool Transport::addExpress(Package &package) {
    if (package.getEstimatedTime() > remainingTime || package.isAlreadyAdded())
        return false;

    carriedPackages.push_back(package);
    remainingTime -= package.getEstimatedTime();
    package.setAdded();
    return true;
}

void Transport::restart() {
    this->carriedPackages.clear();
}

int Transport::calculateProfit() {
    if (carriedPackages.empty()) return profit;

    unsigned totalReward = 0;
    for (auto package: carriedPackages) totalReward += package.getReward();
    profit = (int) totalReward - (int) price;

    return profit;
}

unsigned Transport::sumTime() {
    if (carriedPackages.empty()) return 0;

    unsigned sumTime = 0;
    for (int i = 0; i < carriedPackages.size(); i++)
        sumTime += carriedPackages[i].getEstimatedTime() * (carriedPackages.size() - i);

    return sumTime;
}

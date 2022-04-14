//
// Created by gdrp7 on 30/03/2022.
//

#include "Transport.h"

Transport::Transport(unsigned int price, unsigned int maxVol, unsigned int maxWeight, bool expressDelivery)
        : maxVol(maxVol), maxWeight(maxWeight), price(price),
        remainingVolume(maxVol), remainingWeight(maxWeight),
        profit((int)-price), expressDelivery(expressDelivery){}

unsigned int Transport::getMaxVol() const {
    return maxVol;
}

unsigned int Transport::getMaxWeight() const {
    return maxWeight;
}

void Transport::setWeightExpress(){
    maxWeight = INT_MAX;
}

void Transport::setVolumeExpress(){
    maxWeight = INT_MAX;
}

void Transport::setExpressDelivery(){
    expressDelivery = true;
}

unsigned int Transport::getPrice() const {
    return price;
}

int Transport::getProfit() const {
    if(carriedPackages.empty()) return 0;
    return profit;
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
    profit += (int)package.getReward();
    return true;
}

bool Transport::addExpress(Package &package) {

    if(package.getEstimatedTime() > remainingTime || package.isAlreadyAdded())
        return false;

    carriedPackages.push_back(package);
    remainingTime -= package.getEstimatedTime(); //
    package.setAdded();
    if(remainingTime == 0) full = true;
    return true;
}

void Transport::restart() {
    carriedPackages.clear();
    expressDelivery = false;
}

bool Transport::isExpressDelivery() const {
    return expressDelivery;
}

unsigned int Transport::getDuration() const{
    unsigned int duration = 0;
    for (auto p: carriedPackages) duration += p.getEstimatedTime();
    return duration;
}

unsigned int Transport::getTime() const {
    return time;
}

void Transport::setTime(unsigned int time) {
    Transport::time = time;
}

bool Transport::isFull() const {
    return full;
}

void Transport::setFull(bool full) {
    Transport::full = full;
}

unsigned int Transport::getRemainingTime() const{
    return remainingTime;
}

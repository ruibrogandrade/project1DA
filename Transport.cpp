//
// Created by gdrp7 on 30/03/2022.
//

#include "Transport.h"

Transport::Transport(unsigned int maxVol, unsigned int maxWeight, unsigned int price)
        : maxVol(maxVol), maxWeight(maxWeight), price(price) {}

unsigned int Transport::getMaxVol() const {
    return maxVol;
}

void Transport::setMaxVol(unsigned int maxVol) {
    Transport::maxVol = maxVol;
}

unsigned int Transport::getMaxWeight() const {
    return maxWeight;
}

unsigned int Transport::getPrice() const {
    return price;
}

void Transport::setPrice(unsigned int price) {
    Transport::price = price;
}

void Transport::setMaxWeight(unsigned int maxWeight) {
    Transport::maxWeight = maxWeight;
}

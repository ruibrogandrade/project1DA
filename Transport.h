//
// Created by gdrp7 on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_TRANSPORT_H
#define URBAN_LOGISTICS_TRANSPORT_H

#include "Package.h"
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

class Transport {
private:
    unsigned maxVol{}, remainingVolume{};
    unsigned maxWeight{}, remainingWeight{};
    unsigned price{};
    int profit{};
    unsigned remainingTime = 8 * 3600;
    vector<Package> carriedPackages;

public:
    Transport() = default;
    explicit Transport(unsigned price, unsigned maxVol, unsigned maxWeight);
    unsigned getMaxWeight() const;
    unsigned getMaxVol() const;
    unsigned getPrice() const;
    int getProfit() const;
    int calculateProfit();
    unsigned getRemainingTime() const;
    unsigned getRemainingWeight() const;
    unsigned getRemainingVolume() const;
    const vector<Package> &getCarriedPackages() const;
    unsigned sumTime();
    bool addPackage(Package &package);
    bool addExpress(Package &package);
    void restart();
};


#endif //URBAN_LOGISTICS_TRANSPORT_H

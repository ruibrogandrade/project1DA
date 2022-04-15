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
    unsigned int registration;
    unsigned int maxVol, remainingVolume;
    unsigned int maxWeight, remainingWeight;
    unsigned int price;
    int profit;
    unsigned time;
    unsigned remainingTime = 8 * 3600;

private:
    bool expressDelivery;
    vector<Package> carriedPackages;

public:
    Transport()= default;
    explicit Transport(unsigned int price, unsigned int maxVol, unsigned int maxWeight, bool expressDelivery = false);
    unsigned int getMaxWeight() const;
    unsigned int getMaxVol() const;
    void setWeightExpress();
    void setVolumeExpress();
    unsigned int getPrice() const;
    int calculateProfit();
    int getProfit() const;
    bool isExpressDelivery() const;
    vector<Package> getCarriedPackages() const;
    unsigned int getDuration() const;
    bool addPackage(Package &package);
    bool addExpress(Package &package);
    void setExpressDelivery();
    unsigned int getRemainingTime() const;

    unsigned int getTime() const;

    void setTime(unsigned int time);

    void restart();

     ostream &operator<<(ostream &os) const {
        os << maxVol << "  " << maxWeight << "  " << price;
        return os;
    }
};


#endif //URBAN_LOGISTICS_TRANSPORT_H

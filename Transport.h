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

private:
    bool expressDelivery;
    vector<Package> carriedPackages;

public:
    //When the order is an express delivery we need only to create
    //a constructor like this: Transport(price, expressDelivery)
    Transport(){};
    Transport(unsigned int price, unsigned int maxVol = INT_MAX, unsigned int maxWeight = INT_MAX, bool expressDelivery = false);
    unsigned int getMaxWeight() const;
    unsigned int getMaxVol() const;
    unsigned int getPrice() const;
    bool isExpressDelivery() const;
    const vector<Package> &getCarriedPackages() const;
    unsigned int getRemainingVolume() const;
    unsigned int getRemainingWeight() const;
    bool addPackage(Package &package);
    int getProfit() const;
    void setProfit(int profit);
    void restart();

     ostream &operator<<(ostream &os) {
        os << maxVol << "  " << maxWeight << "  " << price;
        return os;
    }

};


#endif //URBAN_LOGISTICS_TRANSPORT_H

//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_PACKAGE_H
#define URBAN_LOGISTICS_PACKAGE_H

#include <iostream>
using namespace std;

class Package {
private:
    unsigned int volume;
    unsigned int weight;
    unsigned int reward;
    unsigned int estimatedTime;
    bool expressDelivery;
    bool added = false;
public:
    //expressDelivery argument is not necessary in the constructor when the order is not express
    //we need only to create a constructor like this: Package(volume, weight, reward, duration)
    Package() {};
    Package(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int estimatedTime,
            bool expressDelivery = false);
    unsigned int getVolume() const;
    unsigned int getWeight() const;
    unsigned int getReward() const;
    unsigned int getEstimatedTime() const;
    bool isExpressDelivery() const;
    bool isAlreadyAdded() const;
    void setAdded();
    void restart();

};

#endif //URBAN_LOGISTICS_PACKAGE_H

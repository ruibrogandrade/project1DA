//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_PACKAGE_H
#define URBAN_LOGISTICS_PACKAGE_H

#include <iostream>

using namespace std;

class Package {
private:
    unsigned volume = 0, weight = 0;
    unsigned reward = 0, estimatedTime = 0;
    bool added = false;

public:
    Package() = default;
    Package(unsigned volume, unsigned weight, unsigned reward, unsigned estimatedTime);
    unsigned getVolume() const;
    unsigned getWeight() const;
    unsigned getReward() const;
    unsigned getEstimatedTime() const;
    bool isAlreadyAdded() const;
    void setAdded();
    void restart();
};

#endif //URBAN_LOGISTICS_PACKAGE_H

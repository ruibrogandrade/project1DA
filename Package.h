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
    unsigned day = 1;

public:
    /**
     * An empty Constructor
     */
    Package() = default;
    /**
     * Constructor that stores the data after reading the database.
     * @param volume
     * @param weight
     * @param reward
     * @param estimatedTime
     */
    Package(unsigned volume, unsigned weight, unsigned reward, unsigned estimatedTime, unsigned day);
    /**
     * @return unsigned - volume of package
     */
    unsigned getVolume() const;
    /**
     * @return unsigned - weight of package
     */
    unsigned getWeight() const;
    /**
     * @return unsigned - reward of package
     */
    unsigned getReward() const;
    /**
     * @return unsigned - estimated time to delivery the package
     */
    unsigned getEstimatedTime() const;

    unsigned int getDay() const;
};

#endif //URBAN_LOGISTICS_PACKAGE_H

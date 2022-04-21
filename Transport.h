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
    static unsigned id;
    unsigned transportID;
public:
    unsigned int getTransportId() const;

private:
    unsigned maxVol{}, remainingVolume{};
    unsigned maxWeight{}, remainingWeight{};
    unsigned price{};
    int profit{};
    unsigned remainingTime = 8 * 3600;
    vector<Package> carriedPackages;

public:
    /**
     * An empty constructor
     */
    Transport() = default;

    /**
     * Constructor that stores the data after reading the database.
     * @param price
     * @param maxVol
     * @param maxWeight
     */
    explicit Transport(unsigned price, unsigned maxVol, unsigned maxWeight);

    /**
     * @return unsigned - maximum weight supported by the transport.
     */
    unsigned getMaxWeight() const;

    /**
     * @return unsigned - maximum volume supported by the transport.
     */
    unsigned getMaxVol() const;

    /**
     * @return unsigned - cost to use the transport.
     */
    unsigned getPrice() const;

    /**
     *
     * @return int - profit for one transport.
     */
    int getProfit() const;

    /**
     * Calculates the profit based on the price of the transport
     * and the sum of the rewards of the carried packages in the transport.
     * @return int - profit calculated for one transport.
     */
    int calculateProfit();

    /**
     * Returns the remaining time that consists in the available time to deliver
     * the express packages (8 hours) minus the sum of the package times that
     * already been delivered.
     * @return unsigned - remaining time.
     */
    unsigned getRemainingTime() const;

    /**
     *
     * @return vector<Package> - packages that were delivered by the transport.
     */
    const vector<Package> &getCarriedPackages() const;

    /**
     * Calculates the sum of the times to be calculate in the average time.
     * This sum consists in the ordered sum of the packages in the carriedPackages vector.
     *
     * Example: time package 1 + (time package 1 + time package 2) + (time package 1 + time package 2 + time package 3) ...
     * @return
     */
    unsigned sumTime();

    /**
     * This function is used for the normal packages.
     * Verifies if is possible to add the package in the transport according to the weight and
     * the volume, and then add this package in the carriedPackages vector if it is possible.
     * Also decrements the transport's volume, the transport's weight and
     * increments the transport's profit.
     * @param package
     * @return bool - if the package was added or not.
     */
    bool addPackage(Package &package);

    /**
     * This function is used for the express packages.
     * Verifies if is possible to add the package in the transport according to the remaining time,
     * and then add this package in the carriedPackages vector if it is possible.
     * Also decrements the transport's remaining time.
     * @param package
     * @return bool - if the package was added or not.
     */
    bool addExpress(Package &package);

    /**
     * Clear the carriedPackages vector.
     */
    void restart();
};


#endif //URBAN_LOGISTICS_TRANSPORT_H

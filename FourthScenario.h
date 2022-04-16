//
// Created by drigo on 15/04/2022.
//

#ifndef MAIN_CPP_FOURTHSCENARIO_H
#define MAIN_CPP_FOURTHSCENARIO_H

#include "Optimizer.h"
#include "Package.h"
#include "Transport.h"

class FourthScenario {
private:
    /**
     * Compare packages according to their sum of weight and volume.
     * This method is used to when the sort function is called to establish the packages order needed.
     * @param p1 - package 1
     * @param p2 - package 2
     * @return (weight_1 + volume_1) > (weight_2 + volume_2) ? - bool
     */
    static bool comparePackages(const Package &p1, const Package &p2);
public:
    /**
     * Balances the packages in the transports for achieve an approach number of delivered packages
     * per transport.
     * @param packages - all packages that need be delivered.
     * @param transports - all available transports to deliver the packages.
     * @return vector<Transport> - Transports that were used.
     */
    vector<Transport> execute(vector<Package> packages, vector<Transport> transports);
};

#endif //MAIN_CPP_FOURTHSCENARIO_H

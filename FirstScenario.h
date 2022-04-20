//
// Created by Rui Andrade on 09/04/2022.
//

#ifndef MAIN_CPP_FIRSTSCENARIO_H
#define MAIN_CPP_FIRSTSCENARIO_H

#include "Optimizer.h"
#include "Package.h"
#include "Transport.h"

class FirstScenario {
private:
    /**
     * Compare packages according to their sum of weight and volume.
     * This method is used to when the sort function is called to establish the packages order needed.
     * @param p1 - package 1
     * @param p2 - package 2
     * @return (weight_1 + volume_1) > (weight_2 + volume_2) ? - bool
     */
    static bool comparePackages(const Package &p1, const Package &p2);

    /**
     * Compares transports according to their sum of maximum weight and maximum volume.
     * This method is used to when the sort function is called to establish the transports order needed.
     * @param t1 - transport 1
     * @param t2 - transport 2
     * @return (max_weight_1 + max_volume_1) > (max_weight_2 + max_volume_2) ? - bool
     */
    static bool compareTransports(const Transport &t1, const Transport &t2);

public:
    /**
     * Executes the bin-packing first fit algorithm and returns the used transports.
     * @param packages - all packages stored from the database.
     * @param transports - all transports stored from the database.
     * @return vector<Transport> - Transports that were used.
     */
    vector<Transport> execute(vector<Package> &packages, vector<Transport> &transports, vector<Package> &nonDeliveredPackages);
};

#endif //MAIN_CPP_FIRSTSCENARIO_H

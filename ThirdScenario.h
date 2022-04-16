//
// Created by Rui Andrade on 13/04/2022.
//

#ifndef MAIN_CPP_THIRDSCENARIO_H
#define MAIN_CPP_THIRDSCENARIO_H

#include "Package.h"
#include "Transport.h"

class ThirdScenario {
private:
    /**
     * Compare packages according to the lower estimated delivery time.
     * This method is used to when the sort function is called to establish the packages order needed.
     * @param p1 - package 1
     * @param p2 - package 2
     * @return - ( estimated_time_1 < estimated_time_2 )?  (bool)
     */
    static bool comparePackages(const Package &p1, const Package &p2);

    /**
     * Compare transport according to the higher remaining time available for delivery.
     * This method is used to when the sort function is called to establish the transports order needed.
     * @param t1 - transport 1
     * @param t2 - transport 2
     * @return - ( remaining_time_1 > remaining_time_2 )?  (bool)
     */
    static bool compareTransports(const Transport &t1, const Transport &t2);
public:
    /**
     * Executes a bin packing worst fit algorithm and returns the used transports.
     * This function has extra functionality that allows the user to choose
     * how many express transports he wants to use, choosing the best candidates.
     * @param packages - all packages stored from the database.
     * @param transports - all transports stored from the database.
     * @return
     */
    vector<Transport> execute(vector<Package> packages, vector<Transport> transports);
};

#endif //MAIN_CPP_THIRDSCENARIO_H

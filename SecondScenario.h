//
// Created by gdrp7 on 10/04/2022.
//

#ifndef MAIN_CPP_SECONDSCENARIO_H
#define MAIN_CPP_SECONDSCENARIO_H

#include <set>
#include "Package.h"
#include "Transport.h"

class SecondScenario {
public:
    static bool comparePackages(const Package &p1, const Package &p2);

    static bool compareTransports(const Transport &t1, const Transport &t2);

    static void sortPackages(vector<Package> &packages);

    static void sortTransport(vector<Transport> &transports);

    static pair<unsigned, set<unsigned>> knapsack(Transport &t, vector<Package> &packages);
};

#endif //MAIN_CPP_SECONDSCENARIO_H

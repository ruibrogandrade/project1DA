//
// Created by drigo on 15/04/2022.
//

#ifndef MAIN_CPP_FOURTHSCENARIO_H
#define MAIN_CPP_FOURTHSCENARIO_H


#include "Optimizer.h"
#include "Package.h"
#include "Transport.h"

class FourthScenario {
public:
    static bool comparePackages(const Package &p1, const Package &p2);

    static bool compareTransports(const Transport &t1, const Transport &t2);

    static void sortPackages(vector<Package> &packages);

    static void sortTransport(vector<Transport> &transports);
};


#endif //MAIN_CPP_FOURTHSCENARIO_H

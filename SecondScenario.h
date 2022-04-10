//
// Created by Rui Andrade on 10/04/2022.
//

#ifndef MAIN_CPP_SECONDSCENARIO_H
#define MAIN_CPP_SECONDSCENARIO_H
#include "Package.h"
#include "Transport.h"


class SecondScenario {
public:
    static bool comparePackages(const Package &p1, const Package &p2);
    static bool compareTransports(const Transport &t1, const Transport &t2);
    static vector<Package> sortPackages(vector<Package> &packages);
    static vector<Transport> sortTransport(vector<Transport> &transports);
};


#endif //MAIN_CPP_SECONDSCENARIO_H

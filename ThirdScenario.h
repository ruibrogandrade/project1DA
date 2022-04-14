//
// Created by Rui Andrade on 13/04/2022.
//

#ifndef MAIN_CPP_THIRDSCENARIO_H
#define MAIN_CPP_THIRDSCENARIO_H

#include "Package.h"
#include "Transport.h"

class ThirdScenario {
public:
    static bool comparePackages(const Package &p1, const Package &p2);
    static bool compareTransports(const Transport &t1, const Transport &t2);
    static vector<Package> sortPackages(vector<Package> &packages);
    static vector<Transport> sortTransport(vector<Transport> &transports);
    static bool isTransportsFull(vector<Transport> &transports);
};


#endif //MAIN_CPP_THIRDSCENARIO_H

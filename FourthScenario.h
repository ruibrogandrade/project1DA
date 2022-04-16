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
    static bool comparePackages(const Package &p1, const Package &p2);

    static bool compareTransports(const Transport &t1, const Transport &t2);
public:
    vector<Transport> execute(vector<Package> packages, vector<Transport> transports);
};

#endif //MAIN_CPP_FOURTHSCENARIO_H

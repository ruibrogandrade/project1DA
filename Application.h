//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_APPLICATION_H
#define URBAN_LOGISTICS_APPLICATION_H

#include "Package.h"
#include "Transport.h"
#include "Optimizer.h"
#include <vector>

using namespace std;

class Application {
private:
    vector<Package> allPackages;
    vector<Transport> allTransports;
public:
    Application();
    void readPackages();
    void readTransports();
    static unsigned int showMenu();
    void runApplication();
};

#endif //URBAN_LOGISTICS_APPLICATION_H

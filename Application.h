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
    vector<Transport> allTransports, usedTransports;
public:
    Application();
    vector<Package> getAllPackages() const;
    vector<Transport> getAllTransports() const;
    void readPackages();
    void readTransports();
    unsigned int showMenu();
    void showDeliveredPackages() const;
    void showUsedTransports() const;
    void runApplication();
};

#endif //URBAN_LOGISTICS_APPLICATION_H

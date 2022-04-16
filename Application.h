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
    /**
     * Reads the database that contain the transports and another that contain the packages.
     */
    Application();

    /**
     * Reads the packages database and stores the data in allPackages vector.
     */
    void readPackages();

    /**
     * Reads the transports database and stores the data in allTransports vector.
     */
    void readTransports();

    /**
     * Displays the menu and return the chose option entered by the user.
     * @return An option entered by the user (unsigned)
     */
    static unsigned showMenu();

    /**
     * Where the application works. Here the menu is displayed and the specific optimizer and print are called.
     */
    void runApplication();
};

#endif //URBAN_LOGISTICS_APPLICATION_H

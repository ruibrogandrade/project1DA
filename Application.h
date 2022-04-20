//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_APPLICATION_H
#define URBAN_LOGISTICS_APPLICATION_H

#include "FileReader.h"
#include "Package.h"
#include "Transport.h"
#include "Optimizer.h"
#include <vector>
#include <queue>

using namespace std;

class Application {
private:
    FileReader reader;
    Optimizer optimizer;
    queue<vector<Package>> packagesDays, copyPackagesDays;
    queue<vector<Transport>> transportsDays,copyTransportsDays;

private:
    static unsigned showMenu();

    bool processTheDay(unsigned optimizerType);

public:
    /**
     * Reads the database that contain the transports and another that contain the packages.
     */
    Application();

    /**
     * Where the application works. Here the menu is displayed and the specific optimizer and print are called.
     */
    void runApplication();
};

#endif //URBAN_LOGISTICS_APPLICATION_H

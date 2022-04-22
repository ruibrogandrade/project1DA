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
    /**
     * Displays the main menu for the user choose the optimization that he want.
     * @return unsigned - number of the optimization chose.
     */
    static unsigned showMenu();

    /**
     * Process the current day doing the chose optimization by calling the optimizer.
     * @param optimizerType - The type of the optimization chose by the user from the menu.
     * @return bool - If the user want to see the next day or not.
     */
    bool processTheDay(unsigned optimizerType);

    /**
     * Transfers the remaining packages that haven't been delivered from the last day to the next day.
     * @return bool - If the user want to see the next day or not.
     */
    bool nextDay();

public:
    /**
     * Reads the database that contain the transports and another that contain the packages.
     */
    Application();

    /**
     * Where the application works. Here the menu is displayed and the processDay function is called.
     */
    void runApplication();
};

#endif //URBAN_LOGISTICS_APPLICATION_H

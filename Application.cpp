//
// Created by Rui on 30/03/2022.
//

#include "Application.h"
#include <string>
#include <iostream>

using namespace std;

Application::Application() {
}

bool isBadCin() {
    //verify if the menu chose is a possible choice made by the user

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return true;
    }

    return false;
}


unsigned Application::showMenu() {
    cout <<
         "|========================================================================|\n"
         "|          _____________   _________   ______    ___   ___     ___       |\n"
         "|         /  __   __   /  /   _____/  /  __  |  /  /  /  /    /  /       |\n"
         "|        /  / /  / /  /  /   /____   /  / |  | /  /  /  /    /  /        |\n"
         "|       /  / /__/ /  /  /   /____/  /  /  |  |/  /  /  /____/  /         |\n"
         "|      /__/      /__/  /________/  /__/   |_____/  /__________/          |\n"
         "|========================================================================|\n"
         "|      Balance packages by transport        [4]                          |\n"
         "|      Optimize express deliveries          [3]                          |\n"
         "|      Optimize company's profit            [2]                          |\n"
         "|      Optimize the number of transports    [1]                          |\n"
         "|      Exit                                 [0]                          |\n"
         "|========================================================================|\n";

    unsigned int choice;

    while (true) {
        cout << "Choose an option to organize your deliveries:";
        cin >> choice;

        if (isBadCin() || choice < 0 || choice > 4) {
            cout << "Invalid input!" << endl;
            continue;
        }
        return choice;
    }
}

bool wasFinished() {
    unsigned finished;
    while (true) {
        cout << endl << "Press 0 to back to the menu or 1 to finish the program:";
        cin >> finished;
        if (isBadCin() || (finished != 0 && finished != 1)) {
            cout << "Invalid input!" << endl;
            continue;
        }
        return (bool)finished;
    }
}


bool Application::processTheDay(unsigned optimizerType){
    vector<Package> packagesFromFile;
    vector<Transport> transportsFromFile;

    packagesFromFile = copyPackagesDays.front(); copyPackagesDays.pop();
    transportsFromFile = copyTransportsDays.front(); copyTransportsDays.pop();

    optimizer = Optimizer(optimizerType, packagesFromFile, transportsFromFile);
    optimizer.optimize();

    if(copyPackagesDays.empty())
        return false;

    char goToNext;

    cout << endl << "Do you want to see next day of deliveries? (Y/N)" << endl;
    cin >> goToNext;

    size_t oldSize = copyPackagesDays.front().size();

    switch (goToNext) {
        case 'N': case 'n': return false;
        case 'Y': case 'y':
            copyPackagesDays.front().insert(copyPackagesDays.front().begin(),
                                    optimizer.getNonDeliveredPackages().begin(),
                                    optimizer.getNonDeliveredPackages().end());

            cout << endl << copyPackagesDays.front().size() - oldSize << " packages added from last day!";
            return true;
        default: return false;
    }
    
}

void Application::runApplication() {
    unsigned int optimizerType;
    bool nextDay = true;


    packagesDays = reader.getPackagesDays();
    transportsDays = reader.getTransportsDays();

    while (true) {
        optimizerType = showMenu();
        
        if (optimizerType == EXIT) return;

        copyPackagesDays = packagesDays;
        copyTransportsDays = transportsDays;
        
        while(!packagesDays.empty())
        {
            if(!processTheDay(optimizerType))
                break;
        }
        
        if (wasFinished()) return;
    }
}



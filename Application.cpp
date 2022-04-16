//
// Created by Rui on 30/03/2022.
//

#include "Application.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Application::Application() {
    readPackages();
    readTransports();
}

void Application::readPackages() {
    ifstream packagesFile;
    string dataRead, discartedLine;
    unsigned int volume, weight, reward, duration;

    packagesFile.open("../Dados/encomendas.txt", ios::in);
    getline(packagesFile, discartedLine); // discard the first line TITLE

    while (getline(packagesFile, dataRead, ' ')) {
        volume = stoi(dataRead);

        getline(packagesFile, dataRead, ' ');
        weight = stoi(dataRead);

        getline(packagesFile, dataRead, ' ');
        reward = stoi(dataRead);

        getline(packagesFile, dataRead);
        duration = stoi(dataRead);

        allPackages.emplace_back(volume, weight, reward, duration);
    }
}

void Application::readTransports() {
    ifstream packagesFile;
    string dataRead, discartedLine;
    unsigned long maxVol, maxWeight, price;

    packagesFile.open("../Dados/carrinhas.txt", ios::in);
    getline(packagesFile, discartedLine); // discard the first line TITLE

    while (getline(packagesFile, dataRead, ' ')) {
        maxVol = stoi(dataRead);

        getline(packagesFile, dataRead, ' ');
        maxWeight = stoi(dataRead);

        getline(packagesFile, dataRead);
        price = stoi(dataRead);

        allTransports.emplace_back(price, maxVol, maxWeight);
    }
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

unsigned int Application::showMenu() {
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

void Application::runApplication() {
    Optimizer deliveryOptimizer;
    unsigned int optimizerType;

    while (true) {
        optimizerType = showMenu();
        deliveryOptimizer = Optimizer(optimizerType, allPackages, allTransports);

        if (optimizerType == EXIT) return;

        deliveryOptimizer.optimize();

        if (wasFinished()) return;
    }
}



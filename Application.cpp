//
// Created by Rui on 30/03/2022.
//

#include "Application.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void Application::fileReaderPackages() {
    ifstream packagesFile;
    string dataRead, discartedLine;
    unsigned int volume, weight, reward, duration;

    packagesFile.open("../Dados/encomendas.txt", ios::in);
    getline(packagesFile,discartedLine); // discard the first line TITLE

    while(getline(packagesFile,dataRead, ' ')) {
        volume = stoi(dataRead);
        getline(packagesFile,dataRead, ' '); weight = stoi(dataRead);
        getline(packagesFile,dataRead, ' '); reward = stoi(dataRead);
        getline(packagesFile,dataRead); duration = stoi(dataRead);
        package.push_back(Packages(volume, weight, reward, duration));
    }
}

void Application::fileReaderTransport() {
    ifstream packagesFile;
    string dataRead, discartedLine;
    unsigned long maxVol, maxWeight, price;

    packagesFile.open("../Dados/carrinhas.txt", ios::in);
    getline(packagesFile,discartedLine); // discard the first line TITLE

    while(getline(packagesFile,dataRead, ' ')) {
        maxVol = stoi(dataRead);
        getline(packagesFile,dataRead, ' '); maxWeight = stoi(dataRead);
        getline(packagesFile,dataRead); price = stoi(dataRead);
        transport.push_back(Transport(maxVol, maxWeight, price));
    }
}

const vector<Packages> &Application::getPackage() const {
    return package;
}

const vector<Transport> &Application::getTransport() const {
    return transport;
}

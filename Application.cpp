//
// Created by Rui on 30/03/2022.
//

#include "Application.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void Application::fileReaderPackages() {
    int volume, weight, reward, duration;
    string dataRead;
    string packagesPath = "Dados/encomendas.txt", discartedLine;

    ifstream packagesFile;
    packagesFile.open(packagesPath);
    getline(packagesFile,discartedLine); // discard the first line TITLE

    do {
        getline(packagesFile,dataRead, ' '); cout << dataRead;//volume = stoi(dataRead);
        getline(packagesFile,dataRead, ' '); cout << dataRead;//weight = stoi(dataRead);
        getline(packagesFile,dataRead, ' '); cout << dataRead;//reward = stoi(dataRead);
        getline(packagesFile,dataRead); cout << dataRead;//duration = stoi(dataRead);
        //package.push_back(Packages(volume, weight, reward, duration));
    } while(!packagesFile.eof());

    for(auto & i : package) {
        cout << i.getVolume() << " " << i.getWeight() << i.getReward() << i.getDuration() << endl;
    }
}

//
// Created by drigo on 19/04/2022.
//

#include "FileReader.h"
#include <fstream>

FileReader::FileReader() {
    readFiles();
}

void FileReader::readFiles() {
    string prefix = "../Dados/day", sufixP = "Encomendas.txt", sufixT = "Carrinhas.txt";

    string packagesPath = prefix + "1" + sufixP;
    string transportsPath = prefix + "1" + sufixT;

    while(readPackages(packagesPath) && readTransports(transportsPath))
    {
        packagesDays.push(packagesInFile);
        transportsDays.push(transportsInFile);

        packagesPath = prefix + to_string(++day) + sufixP;
        transportsPath = prefix + to_string(day) + sufixT;
    }
}

bool FileReader::readPackages(const string& filePath) {
    packagesInFile.clear();
    ifstream file;
    string dataRead, droppedLine;
    unsigned int volume, weight, reward, duration;

    file.open(filePath, ios::in);

    if(!file.is_open())
        return false;

    getline(file, droppedLine); // discard the first line TITLE

    while (getline(file, dataRead, ' ')) {
        volume = stoi(dataRead);

        getline(file, dataRead, ' ');
        weight = stoi(dataRead);

        getline(file, dataRead, ' ');
        reward = stoi(dataRead);

        getline(file, dataRead);
        duration = stoi(dataRead);

        packagesInFile.emplace_back(volume, weight, reward, duration, day);
    }

    file.close();
    return true;
}

bool FileReader::readTransports(const string& filePath) {
    transportsInFile.clear();

    ifstream file;
    string dataRead, droppedLine;
    unsigned long maxVol, maxWeight, price;

    file.open(filePath, ios::in);

    if(!file.is_open())
        return false;

    getline(file, droppedLine); // drop the first line TITLE

    while (getline(file, dataRead, ' ')) {
        maxVol = stoi(dataRead);

        getline(file, dataRead, ' ');
        maxWeight = stoi(dataRead);

        getline(file, dataRead);
        price = stoi(dataRead);

        transportsInFile.emplace_back(price, maxVol, maxWeight);
    }

    file.close();
    return true;
}

const queue<vector<Package>> &FileReader::getPackagesDays() const {
    return packagesDays;
}

const queue<vector<Transport>> &FileReader::getTransportsDays() const {
    return transportsDays;
}

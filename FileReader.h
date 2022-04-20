//
// Created by drigo on 19/04/2022.
//

#ifndef MAIN_CPP_FILEREADER_H
#define MAIN_CPP_FILEREADER_H

#include "Package.h"
#include "Transport.h"
#include "Optimizer.h"
#include <vector>
#include <queue>

class FileReader {
private:
    queue<vector<Package>> packagesDays;
    queue<vector<Transport>> transportsDays;
    vector<Package> packagesInFile;
    vector<Transport> transportsInFile;
    unsigned day = 1;

private:
    void readFiles();

    bool readPackages(const string& filePath);

    bool readTransports(const string& filePath);

public:
    FileReader();

    const queue<vector<Package>> &getPackagesDays() const;

    const queue<vector<Transport>> &getTransportsDays() const;
};


#endif //MAIN_CPP_FILEREADER_H

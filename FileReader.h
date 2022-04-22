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
    /**
     * Calls the readPackages and the readTransports functions and increment
     * the package vectors' queue and the transport vectors' queue according to
     * the number of days available.
     */
    void readFiles();

    /**
     * Reads the packages and stores them in the packagesInfFile vector for one day.
     * @param filePath - packages path for one day.
     * @return bool - If the filePath could be opened or not.
     */
    bool readPackages(const string& filePath);

    /**
     * Reads the transports and stores them in the transportsInfFile vector for one day.
     * @param filePath - transports path for one day.
     * @return bool - If the filePath could be opened or not.
     */
    bool readTransports(const string& filePath);

public:

    /**
     * Calls the readFiles function.
     */
    FileReader();

    /**
     *
     * @return queue<vector<Package>> - Packages that will be processed day by day.
     * Each vector into the queue corresponding to the packages of one day.
     */
    const queue<vector<Package>> &getPackagesDays() const;

    /**
     *
     * @return queue<vector<Transport>> - Transports that will be processed day by day.
     * Each vector into the queue corresponding to the transports of one day.
     */
    const queue<vector<Transport>> &getTransportsDays() const;
};


#endif //MAIN_CPP_FILEREADER_H

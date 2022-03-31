//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_APPLICATION_H
#define URBAN_LOGISTICS_APPLICATION_H

#include "Packages.h"
#include "Transport.h"
#include <vector>
using namespace std;

class Application {
private:
    vector<Packages> package;
    vector<Transport> transport;
public:
    const vector<Packages> &getPackage() const;
    const vector<Transport> &getTransport() const;
public:
    void fileReaderPackages();
    void fileReaderTransport();
};


#endif //URBAN_LOGISTICS_APPLICATION_H

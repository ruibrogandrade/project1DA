//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_APPLICATION_H
#define URBAN_LOGISTICS_APPLICATION_H

#include "Packages.h"
#include <vector>
using namespace std;

class Application {
private:
    vector<Packages> package;
public:
    void fileReaderPackages();
};


#endif //URBAN_LOGISTICS_APPLICATION_H

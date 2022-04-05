//
// Created by Rui on 04/04/2022.
//

#include <algorithm>
#include "Optimizer.h"

using namespace std;

bool Optimizer::comparePackages(const Package &p1, const Package &p2) {
    double ratio1 = p1.getWeight()/p1.getVolume();
    double ratio2 = p2.getWeight()/p2.getVolume();
    return ratio1 < ratio2;
}

bool Optimizer::compareTransports(const Transport& t1, const Transport& t2){
    double ratio1 = t1.getMaxWeight()/t1.getMaxVol();
    double ratio2 = t2.getMaxWeight()/t2.getMaxVol();
    return ratio1 < ratio2;
}

vector<Package> Optimizer::sortPackages(vector<Package> &packages) {
    sort(packages.begin(), packages.end(), comparePackages);
    return packages;
}

vector<Transport> Optimizer::sortTransport(vector<Transport> &transports) {
    sort(transports.begin(), transports.end(), compareTransports);
    return transports;
}

Optimizer::Optimizer(unsigned int optimizerType, const vector<Package> &allPackages, const vector<Transport> &allTransports) {
    this->optimizerType = optimizerType;
    this->allPackages = allPackages;
    this->allTransports = allTransports;
}

void Optimizer::optimize() {
    switch (optimizerType)
    {
        case OPTIMIZE_TRANSPORTS: optimizeTransports(); break;
        case OPTIMIZE_PROFIT: optimizeProfit(); break;
        case OPTIMIZE_EXPRESS_DELIVERY: optimizeExpressDelivery(); break;
    }
}

void Optimizer::optimizeTransports() {

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    sort(packages.begin(), packages.end(), comparePackages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    sort(transports.begin(), transports.end(), compareTransports);

    for(auto transport : transports)
    {
        usedTransports.push_back(transport);

        for(auto package : packages)
        {
            transport.addPackage(package);
        }
    }
}

vector<Transport> Optimizer::getUsedTransports() const {
    return usedTransports;
}

void Optimizer::optimizeProfit(){
    //TODO
};

void Optimizer::optimizeExpressDelivery(){
    //TODO
}



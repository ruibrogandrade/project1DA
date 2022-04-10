//
// Created by Rui on 04/04/2022.
//

#include <algorithm>
#include "Optimizer.h"
#include "FirstScenario.h"

using namespace std;

Optimizer::Optimizer(unsigned int optimizerType, const vector<Package> &allPackages, const vector<Transport> &allTransports) {
    this->optimizerType = optimizerType;
    this->allPackages = allPackages;
    this->allTransports = allTransports;
}

void Optimizer::optimize() {
    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS: optimizeTransports(); break;
        case OPTIMIZE_PROFIT: optimizeProfit(); break;
        case OPTIMIZE_EXPRESS_DELIVERY: optimizeExpressDelivery(); break;
    }
}

void Optimizer::optimizeTransports() {
    cleanUsedTransports();

    vector<Package> packages = FirstScenario::sortPackages(allPackages); // Make a copy of the packages for don't change the original vector
    vector<Transport> transports = FirstScenario::sortTransport(allTransports); // Make a copy of the transports for don't change the original vector

    /*
    for (auto &package: packages)
        for (auto &t: transports)
            if (t.addPackage(package\))
                break;

    int counter = 0;
    for (const auto& t:transports) if(!t.getCarriedPackages().empty()) counter++;
    cout << counter << endl;
    */

    for(auto t : transports) {
        for (auto p = packages.begin(); p != packages.end(); p++) {

            if(t.getRemainingVolume() == 0 || t.getRemainingWeight() == 0) break;

            if(t.addPackage(*p)) packages.erase(p);

            if(packages.empty()) {
                usedTransports.push_back(t);
                cout << usedTransports.size() << endl;
                return;
            }
        }
        usedTransports.push_back(t);
    }
}

vector<Transport> Optimizer::getUsedTransports() const {
    return usedTransports;
}

void Optimizer::optimizeProfit(){
    //TODO
}

void Optimizer::optimizeExpressDelivery(){
    //TODO
}

void Optimizer::cleanUsedTransports() {
    this->usedTransports.clear();
}
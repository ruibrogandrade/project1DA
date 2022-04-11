//
// Created by Rui on 04/04/2022.
//

#include <algorithm>
#include "Optimizer.h"
#include "FirstScenario.h"
#include "SecondScenario.h"

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
    restartOptimizer();

    //vector<Package> packages = FirstScenario::sortPackages(allPackages); // Make a copy of the packages for don't change the original vector
    vector<Transport> transports = FirstScenario::sortTransport(allTransports); // Make a copy of the transports for don't change the original vector

    for (auto &package: allPackages)
        for (auto &transport: transports)
            if (transport.addPackage(package))
                break;

    for (const auto& transport:transports) {
        if(transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
    }

    /*for(auto t : transports) {
        for (auto p = packages.begin(); p != packages.end(); p++) {

            if(t.getRemainingVolume() == 0 || t.getRemainingWeight() == 0) break;

            if(t.addPackage(*p)) packages.erase(p);

            if(packages.empty()) {
                usedTransports.push_back(t);
                return;
            }
        }
        usedTransports.push_back(t);
    }*/
}

vector<Transport> Optimizer::getUsedTransports() const {
    return usedTransports;
}

void Optimizer::optimizeProfit(){
    //TODO
    restartOptimizer();

    vector<Package> packages = SecondScenario::sortPackages(allPackages); // Make a copy of the packages for don't change the original vector
    vector<Transport> transports = SecondScenario::sortTransport(allTransports); // Make a copy of the transports for don't change the original vector

    for (auto &t: transports) SecondScenario::knapSack(t, packages);
}

void Optimizer::optimizeExpressDelivery(){
    //TODO
    restartOptimizer();

}

void Optimizer::restartOptimizer() {
    usedTransports.clear();

    for(auto &package : allPackages)
        package.restart(); // makes added = false and expressDelivery = false

    for(auto &transport : allTransports) // makes carriedPackages empty and expressDelivery = false
        transport.restart();
}

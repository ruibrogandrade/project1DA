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
        case OPTIMIZE_TRANSPORTS: optimizeTransports(); showUsedTransports(); break;
        case OPTIMIZE_PROFIT: optimizeProfit(); showUsedTransports(); break;
        case OPTIMIZE_EXPRESS_DELIVERY: optimizeExpressDelivery(); showUsedTransports(); break;
    }
}

void Optimizer::optimizeTransports() {
    restartOptimizer();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    packages = FirstScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    transports = FirstScenario::sortTransport(transports);

    for (auto &package: packages)
        for (auto &transport: transports)
            if (transport.addPackage(package))
                break;

    for (const auto& transport: transports) {
        if(transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
    }
}

void Optimizer::optimizeProfit(){
    restartOptimizer();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    packages = SecondScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    transports = SecondScenario::sortTransport(transports);

    totalProfit = 0;

    for (auto t: transports) {
        auto temp = SecondScenario::knapSack(t, packages);
        if(temp.first-t.getPrice()<0) return;
        else {
            totalProfit += temp.first-t.getPrice();
            for (auto rit = temp.second.rbegin(); rit != temp.second.rend(); rit++ ) {
                t.addPackage(packages[*rit]);
                packages.erase(packages.begin() + *rit);
            }
            usedTransports.push_back(t);
        }

    }

    /*
    for (auto &package: packages)
        for (auto &transport: transports)
            if (transport.addPackage(package))
                break;

    for (auto& transport: transports)
    {
        if (transport.getCarriedPackages().empty())
            break;

        int profit = transport.calculateProfit()
        if(profit > 0)
        {
            usedTransports.push_back(transport);
            totalProfit += profit;
        }
    }
     */
}

void Optimizer::optimizeExpressDelivery(){
    //TODO
    restartOptimizer();
}

void Optimizer::restartOptimizer() {
    usedTransports.clear();

    for(auto &package : allPackages)
        package.restart(); // makes package.added = false and expressDelivery = false

    for(auto &transport : allTransports) // makes transport.carriedPackages empty and expressDelivery = false
        transport.restart();
}

vector<Transport> Optimizer::getUsedTransports() const {
    return usedTransports;
}

void Optimizer::showUsedTransports() const {

    switch (optimizerType)
    {
        case OPTIMIZE_TRANSPORTS:
            cout << endl << "Number of transports that were used: " << usedTransports.size() << endl << endl;
            cout << "Transports                        Number of carried packages" << endl;

            for(const auto& transport : usedTransports)
            {
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------  " << transport.getCarriedPackages().size() << endl;
            }
            break;

        case OPTIMIZE_PROFIT:
            cout << endl << "Number of transports that were used: " << usedTransports.size() << endl
             << "Total profit: " << totalProfit << endl << endl;
            cout << "Transports                        Number of carried packages                         Profit" << endl;

            for(auto transport : usedTransports)
            {
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------               " << transport.getCarriedPackages().size()
                     << "             --------------------   " << transport.calculateProfit() << endl;
            }
            break;
    }
}


/*
 for(auto transport : transports)
    {
        unsigned int sizeVolume = transport.getMaxVol(), sizeWeight = transport.getMaxWeight();
        vector<unsigned int> maxProfitVolume(sizeVolume, 0), maxProfitWeight(sizeWeight, 0);

        for(size_t i = 0; i < packages.size(); i++)
        {
            unsigned int volume = packages[i].getVolume(), weight = packages[i].getWeight();

            while(volume < transport.getMaxVol() || weight < transport.getMaxWeight())
            {
                if(packages[i].getReward() + maxProfitVolume[volume - packages[i].getVolume()] > maxProfitVolume[volume])
                {
                    maxProfitVolume[volume] = packages[i].getReward() + maxProfitVolume[volume - packages[i].getVolume()];
                }
            }
        }
    }

 */
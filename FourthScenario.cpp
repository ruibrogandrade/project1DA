//
// Created by drigo on 15/04/2022.
//

#include <algorithm>
#include "FourthScenario.h"

bool FourthScenario::comparePackages(const Package &p1, const Package &p2) {
    double sum1 = p1.getWeight() + p1.getVolume();
    double sum2 = p2.getWeight() + p2.getVolume();
    return sum1 > sum2;
}

vector<Transport> FourthScenario::execute(vector<Package> packages, vector<Transport> transports) {
    sort(packages.begin(), packages.end(), comparePackages);

    vector<Transport> usedTransports = {};

    auto transportIter = transports.begin();
    for(auto package : packages) {
        bool added = true;
        while(!transportIter->addPackage(package)) {
            added = false;
            transportIter++;
            if(transportIter == transports.end()) {
                transportIter = transports.begin();
                break;
            }
        }

        if(added) {
            transportIter++;
            if(transportIter == transports.end())
                transportIter = transports.begin();
        }
    }
    for (const auto &t: transports) {
        if (t.getCarriedPackages().empty()) break;
        usedTransports.push_back(t);
    }
    return usedTransports;
}
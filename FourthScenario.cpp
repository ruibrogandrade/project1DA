//
// Created by drigo on 15/04/2022.
//

#include <algorithm>
#include "FourthScenario.h"

bool FourthScenario::comparePackages(const Package &p1, const Package &p2) {
    double sum1 = p1.getWeight() + p1.getVolume();
    double sum2 = p2.getWeight() + p2.getVolume();


    if(p1.getDay() == p2.getDay())
        return sum1 > sum2;

    return p1.getDay() < p2.getDay();
}

bool FourthScenario::compareTransports(const Transport &t1, const Transport &t2) {
    return t1.getMaxWeight() + t1.getMaxVol() > t2.getMaxWeight() + t2.getMaxVol();
}

vector<Transport> FourthScenario::execute(vector<Package> packages, vector<Transport> transports) {
    sort(packages.begin(), packages.end(), comparePackages);
    sort(transports.begin(), transports.end(), compareTransports);

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

const vector<Package> &FourthScenario::getNonDeliveredPackages() const {
    return nonDeliveredPackages;
}

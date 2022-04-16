//
// Created by Rui Andrade on 09/04/2022.
//

#include <algorithm>
#include "FirstScenario.h"

bool FirstScenario::comparePackages(const Package &p1, const Package &p2) {
    double sum1 = p1.getWeight() + p1.getVolume();
    double sum2 = p2.getWeight() + p2.getVolume();
    return sum1 > sum2;
}

bool FirstScenario::compareTransports(const Transport& t1, const Transport& t2){
    double sum1 = t1.getMaxWeight() + t1.getMaxVol();
    double sum2 = t2.getMaxWeight() + t2.getMaxVol();
    return sum1 > sum2;
}

vector<Transport> FirstScenario::execute(vector<Package> packages, vector<Transport> transports) {
    sort(packages.begin(), packages.end(), comparePackages);
    sort(transports.begin(), transports.end(), compareTransports);

    vector<Transport> usedTransports = {};

    for (auto &package: packages)
        for (auto &transport: transports)
            if (transport.addPackage(package))
                break;

    for (const auto &t: transports) {
        if (t.getCarriedPackages().empty()) break;
        usedTransports.push_back(t);
    }
    return usedTransports;
}

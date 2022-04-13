//
// Created by Rui Andrade on 13/04/2022.
//

#include <algorithm>
#include "ThirdScenario.h"


bool ThirdScenario::comparePackages(const Package &p1, const Package &p2) {
    return p1.getEstimatedTime()/(p1.getVolume() + p1.getWeight()) > p2.getEstimatedTime()/(p2.getVolume() + p2.getWeight());
}

bool ThirdScenario::compareTransports(const Transport &t1, const Transport &t2) {
    return (t1.getMaxWeight() + t1.getMaxVol()) < (t2.getMaxWeight() + t2.getMaxVol());
}

vector<Package> ThirdScenario::sortPackages(vector<Package> &packages) {
    sort(packages.begin(), packages.end(), comparePackages);
    return packages;
}

vector<Transport> ThirdScenario::sortTransport(vector<Transport> &transports) {
    sort(transports.begin(), transports.end(), compareTransports);
    return transports;
}

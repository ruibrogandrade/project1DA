//
// Created by Rui Andrade on 13/04/2022.
//

#include <algorithm>
#include "ThirdScenario.h"


bool ThirdScenario::comparePackages(const Package &p1, const Package &p2) {
    return p1.getEstimatedTime() < p2.getEstimatedTime();
}

bool ThirdScenario::compareTransports(const Transport &t1, const Transport &t2) {
    return t1.getRemainingTime() > t2.getRemainingTime();
}

vector<Package> ThirdScenario::sortPackages(vector<Package> &packages) {
    sort(packages.begin(), packages.end(), comparePackages);
    return packages;
}

vector<Transport> ThirdScenario::sortTransport(vector<Transport> &transports) {
    sort(transports.begin(), transports.end(), compareTransports);
    return transports;
}

bool ThirdScenario::isTransportsFull(vector<Transport> &transports) {
    for (const auto &t: transports)
        if (!t.isFull()) return false;
    return true;
}

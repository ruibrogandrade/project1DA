//
// Created by Rui Andrade on 09/04/2022.
//

#include <algorithm>
#include "FirstScenario.h"
#include "Transport.h"

bool FirstScenario::comparePackages(const Package &p1, const Package &p2) {
    unsigned int ratio1 = p1.getWeight()+p1.getVolume();
    unsigned int ratio2 = p2.getWeight()+p2.getVolume();
    return ratio1 < ratio2;
}

bool FirstScenario::compareTransports(const Transport& t1, const Transport& t2){
    double ratio1 = (double)t1.getMaxWeight()/t1.getMaxVol();
    double ratio2 = (double)t2.getMaxWeight()/t2.getMaxVol();
    return ratio1 < ratio2;
}

vector<Package> FirstScenario::sortPackages(vector<Package> &packages) {
    sort(packages.begin(), packages.end(), comparePackages);
    return packages;
}

vector<Transport> FirstScenario::sortTransport(vector<Transport> &transports) {
    sort(transports.begin(), transports.end(), compareTransports);
    return transports;
}
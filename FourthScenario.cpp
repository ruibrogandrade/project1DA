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

bool FourthScenario::compareTransports(const Transport& t1, const Transport& t2){
    double sum1 = t1.getRemainingVolume() + t1.getRemainingWeight();
    double sum2 = t2.getRemainingVolume() + t2.getRemainingWeight();
    return sum1 > sum2;
}

void FourthScenario::sortPackages(vector<Package> &packages) {
    sort(packages.begin(), packages.end(), comparePackages);
}

void FourthScenario::sortTransport(vector<Transport> &transports) {
    sort(transports.begin(), transports.end(), compareTransports);
}
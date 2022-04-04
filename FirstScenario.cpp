//
// Created by Rui on 04/04/2022.
//

#include <algorithm>
#include "FirstScenario.h"

using namespace std;

bool FirstScenario::comparePackages(const Packages &p1, const Packages &p2) {
    double ratio1 = p1.getWeight()/p1.getVolume();
    double ratio2 = p2.getWeight()/p2.getVolume();
    return ratio1 < ratio2;
}

bool FirstScenario::compareTransport(const Transport& t1, const Transport& t2){
    double ratio1 = t1.getMaxWeight()/t1.getMaxVol();
    double ratio2 = t2.getMaxWeight()/t2.getMaxVol();
    return ratio1 < ratio2;
}

vector<Packages> FirstScenario::sortPackages(vector<Packages> &v) {
    sort(v.begin(), v.end(), comparePackages);
    return v;
}

vector<Transport> FirstScenario::sortTransport(vector<Transport> &v) {
    sort(v.begin(), v.end(), compareTransport);
    return v;
}

void FirstScenario::greedyImplementation(vector<Packages> &p, vector<Transport> &t) {
    vector<Packages> pack = sortPackages(p);
    vector<Transport> res = sortTransport(t);
    for(auto i : t) {
        for(auto j : p) {
            if(i.getMaxVol() > j.getVolume() && i.getMaxWeight() > j.getWeight()) {
                i.setMaxVol(i.getMaxVol() - j.getVolume());
                i.setMaxWeight(i.getMaxWeight() - j.getWeight());
            }
            else break;
        }
    }
    for ( auto r : res) r;
}
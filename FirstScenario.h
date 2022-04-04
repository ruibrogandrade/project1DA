//
// Created by Rui on 04/04/2022.
//

#ifndef MAIN_CPP_FIRSTSCENARIO_H
#define MAIN_CPP_FIRSTSCENARIO_H

#include "Application.h"

class FirstScenario {
public:
    static bool comparePackages(const Packages& p1, const Packages& p2);
    static bool compareTransport(const Transport& t1, const Transport& t2);
    vector<Packages> sortPackages(vector<Packages> &v);
    vector<Transport> sortTransport(vector<Transport> &v);
    void greedyImplementation(vector<Packages> &p, vector<Transport> &t);
};

#endif //MAIN_CPP_FIRSTSCENARIO_H

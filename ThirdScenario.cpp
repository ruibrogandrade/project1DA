//
// Created by Rui Andrade on 13/04/2022.
//

#include <algorithm>
#include "ThirdScenario.h"

bool ThirdScenario::comparePackages(const Package &p1, const Package &p2) {

    if(p1.getDay() == p2.getDay())
        return p1.getEstimatedTime() < p2.getEstimatedTime();

    return p1.getDay() < p2.getDay();
}

bool ThirdScenario::compareTransports(const Transport &t1, const Transport &t2) {
    return t1.getRemainingTime() > t2.getRemainingTime();
}

vector<Transport> ThirdScenario::execute(vector<Package> packages, vector<Transport> transports) {
    sort(packages.begin(), packages.end(), comparePackages);
    sort(transports.begin(), transports.end(), compareTransports);

    vector<Transport> usedTransports = {};

    unsigned numOfTransports;
    while (true) {
        cout << endl << "How many transports you want to use (1 - " << transports.size() << ")?:";
        cin >> numOfTransports;
        if (!cin.fail() && cin.peek() == '\n' && numOfTransports >= 1 && numOfTransports <= transports.size())
            break;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid number!" << endl;
    }
    transports.resize(numOfTransports);

    auto it = transports.begin();
    for (auto package: packages) {
        if (!(it->addExpress(package))) break;

        if (it->getRemainingTime() < (it++)->getRemainingTime()) it++;

        if (it == transports.end()) it = transports.begin();
    }

    unsigned sumTime = 0;
    for (auto &transport: transports) {
        if (transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
        sumTime += transport.sumTime();
    }
    return usedTransports;
}

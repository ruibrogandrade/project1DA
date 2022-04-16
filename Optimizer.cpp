//
// Created by Rui on 04/04/2022.
//

#define GREEDY 1
#define KNAPSACK 0

#include <algorithm>
#include "Optimizer.h"
#include "FirstScenario.h"
#include "SecondScenario.h"
#include "ThirdScenario.h"
#include "FourthScenario.h"
#include <cmath>

using namespace std;

Optimizer::Optimizer(unsigned optimizerType, const vector<Package> &allPackages,
                     const vector<Transport> &allTransports) {
    this->optimizerType = optimizerType;
    this->allPackages = allPackages;
    this->allTransports = allTransports;
}

void Optimizer::optimize() {
    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS:
            optimizeTransports();
            showUsedTransports();
            break;
        case OPTIMIZE_PROFIT:
            optimizeProfit();
            showUsedTransports();
            break;
        case OPTIMIZE_EXPRESS_DELIVERY:
            optimizeExpressDelivery();
            showUsedTransports();
            break;
        case BALANCE_PACKAGES:
            balancePackages();
            showUsedTransports();
    }
}

void Optimizer::optimizeTransports() {
    restartOptimizer();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    FirstScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    FirstScenario::sortTransport(transports);

    for (auto &package: packages)
        for (auto &transport: transports)
            if (transport.addPackage(package))
                break;

    for (const auto &transport: transports) {
        if (transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
        numDeliveredPackages += transport.getCarriedPackages().size();
    }
    efficiency = (double) numDeliveredPackages / (double) packages.size();
    efficiency = round(efficiency * 10000.0) / 10000.0;
}

unsigned chooseProfitAlgorithm() {
    cout << endl <<
         "|========================================================================|\n"
         "|      Greedy Algorithm (fast, but only an approach)     [1]             |\n"
         "|      Knapsack Algorithm (precise, but so slow)         [0]             |\n"
         "|========================================================================|\n";
    while (true) {
        cout << "Choose an algorithm that you want to use for achieve better profit:";
        unsigned algorithmChose;

        cin >> algorithmChose;
        if (cin.fail() || cin.peek() != '\n' || (algorithmChose != 1 && algorithmChose != 0)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        return algorithmChose;
    }
}

void Optimizer::greedyProfit(vector<Package> &packages, vector<Transport> &transports) {
    for (auto &package: packages)
        for (auto &transport: transports)
            if (transport.addPackage(package))
                break;

    for (auto &transport: transports) {
        if (transport.getCarriedPackages().empty()) break;

        int profit = transport.calculateProfit();
        if (profit > 0) {
            usedTransports.push_back(transport);
            numDeliveredPackages += transport.getCarriedPackages().size();
            totalProfit += profit;
        }
    }
    efficiency = (double) numDeliveredPackages / (double) packages.size();
    efficiency = round(efficiency * 10000.0) / 10000.0;

}

void Optimizer::knapsackProfit(vector<Package> &packages, vector<Transport> &transports) {
    for (auto t: transports) {
        auto temp = SecondScenario::knapsack(t, packages);
        int profit = (int) (temp.first - t.getPrice());
        if (profit < 0) return;
        totalProfit += profit;
        for (auto rit = temp.second.rbegin(); rit != temp.second.rend(); rit++) {
            t.addPackage(packages[*rit]);
            packages.erase(packages.begin() + *rit);
        }
        usedTransports.push_back(t);
        numDeliveredPackages += t.getCarriedPackages().size();
    }
    efficiency = (double) numDeliveredPackages / (double) packages.size();
    efficiency = round(efficiency * 10000.0) / 10000.0;
}


void Optimizer::optimizeProfit() {
    restartOptimizer();

    unsigned algorithmSelected = chooseProfitAlgorithm();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    SecondScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    SecondScenario::sortTransport(transports);

    if (algorithmSelected == GREEDY) greedyProfit(packages, transports);
    else if (algorithmSelected == KNAPSACK) knapsackProfit(packages, transports);
}


void Optimizer::optimizeExpressDelivery() {
    restartOptimizer();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    ThirdScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    ThirdScenario::sortTransport(transports);

    unsigned numOfTransports;
    while (true) {
        cout << endl << "How many transports you want to use (1 - " << allTransports.size() << ")?:";
        cin >> numOfTransports;
        if (!cin.fail() && cin.peek() == '\n' && numOfTransports >= 1 && numOfTransports <= allTransports.size())
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
        numDeliveredPackages += transport.getCarriedPackages().size();
    }

    avgTime = (double) sumTime / numDeliveredPackages;
    efficiency = (double) numDeliveredPackages / (double) packages.size();
    efficiency = round(efficiency * 10000.0) / 10000.0;
}

void Optimizer::balancePackages() {
    restartOptimizer();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    FourthScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector

    for(auto package : packages)
    {
        FourthScenario::sortTransport(transports);
        auto transport = transports.begin();

        while(!transport->addPackage(package))
        {
            transport++;
            if(transport == transports.end())
                break;
        }
    }

    for(const auto& transport : transports)
    {
        if(!transport.getCarriedPackages().empty())
        {
            usedTransports.push_back(transport);
            numDeliveredPackages += transport.getCarriedPackages().size();
        }
    }

    efficiency = (double) numDeliveredPackages / (double) packages.size();
    efficiency = round(efficiency * 10000.0) / 10000.0;
}

void Optimizer::restartOptimizer() {
    usedTransports.clear();

    // makes package.added = false
    for (auto &package: allPackages)
        package.restart();

    // makes transport.carriedPackages empty
    for (auto &transport: allTransports)
        transport.restart();

    totalProfit = 0;
    numDeliveredPackages = 0;
    avgTime = 0, efficiency = 0;
}

void Optimizer::showUsedTransports() const {
    cout << endl << "Used transports: " << usedTransports.size() << endl
         << "Delivered packages: " << numDeliveredPackages << endl
         << "NON delivered packages: " << allPackages.size() - numDeliveredPackages << endl
         << "Efficiency: " << efficiency * 100 << "%" << endl;

    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS: case BALANCE_PACKAGES:
            cout << endl << "Transports" << "                        "
                 << "Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  "
                << transport.getMaxWeight() << "  "
                << transport.getPrice() << "  ---------------  "
                << transport.getCarriedPackages().size() << endl;
            break;

        case OPTIMIZE_PROFIT:
            cout << "Total profit: " << totalProfit << endl << endl;
            cout << "Transports" << "                           "
                 << "Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  "
                << transport.getMaxWeight() << "  "
                << transport.getPrice() << "  ---------------               "
                << transport.getCarriedPackages().size() << "             --------------------   "
                << transport.getProfit() << endl;
            break;

        case OPTIMIZE_EXPRESS_DELIVERY:
            cout << "Minimum Average Time: " << avgTime << endl << endl;
            cout << "Transports" << "                           "
                 << "Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  "
                << transport.getMaxWeight() << "  "
                << transport.getPrice() << "  ---------------  "
                << transport.getCarriedPackages().size() << endl;
            break;
    }
}


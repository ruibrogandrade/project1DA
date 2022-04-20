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

    FirstScenario firstScenario;
    vector<Transport> result =
            firstScenario.execute(allPackages, allTransports, nonDeliveredPackages);

    this->usedTransports = result;
    calculateEfficiency();
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

void Optimizer::optimizeProfit() {
    restartOptimizer();

    unsigned algorithmSelected = chooseProfitAlgorithm();

    SecondScenario secondScenario;
    vector<Transport> result;

    if (algorithmSelected == GREEDY)
        secondScenario.greedyProfit(allPackages, allTransports);
    else if (algorithmSelected == KNAPSACK)
        secondScenario.knapsackProfit(allPackages, allTransports);

    usedTransports = secondScenario.getUsedTransports();
    totalProfit = secondScenario.getTotalProfit();
    calculateEfficiency();
}


void Optimizer::optimizeExpressDelivery() {
    restartOptimizer();

    ThirdScenario thirdScenario;
    vector<Transport> result =
            thirdScenario.execute(allPackages, allTransports);

    this->usedTransports = result;
    calculateEfficiency();
    calculateAverageTime();
}

void Optimizer::balancePackages() {
    restartOptimizer();

    FourthScenario fourthScenario;
    vector<Transport> result =
            fourthScenario.execute(allPackages, allTransports);

    this->usedTransports = result;
    calculateEfficiency();
}

void Optimizer::restartOptimizer() {
    usedTransports.clear();
    nonDeliveredPackages.clear();

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
         << "NON delivered packages: " << nonDeliveredPackages.size() << endl
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
            cout << "Transports" << "                        "
                 << "Number of carried packages" << "                         "
                 << "Profit" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  "
                << transport.getMaxWeight() << "  "
                << transport.getPrice() << "  ---------------               "
                << transport.getCarriedPackages().size() << "             --------------------   "
                << transport.getProfit() << endl;
            break;

        case OPTIMIZE_EXPRESS_DELIVERY:
            cout << "Minimum Average Time: " << avgTime << endl << endl;
            cout << "Transports" << "                        "
                 << "Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  "
                << transport.getMaxWeight() << "  "
                << transport.getPrice() << "  ---------------  "
                << transport.getCarriedPackages().size() << endl;
            break;
    }
}

void Optimizer::calculateEfficiency() {
    for (const auto& t : usedTransports)
        numDeliveredPackages += t.getCarriedPackages().size();

    this->efficiency = (double) numDeliveredPackages / (double) allPackages.size();
    this->efficiency = round(efficiency * 10000.0) / 10000.0;
}

void Optimizer::calculateAverageTime() {
    unsigned sumTime = 0;
    for (auto &transport: usedTransports) sumTime += transport.sumTime();

    this->avgTime = (double) sumTime / numDeliveredPackages;
}

const vector<Package> &Optimizer::getNonDeliveredPackages() const {
    return nonDeliveredPackages;
}

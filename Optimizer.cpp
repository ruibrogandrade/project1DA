//
// Created by Rui on 04/04/2022.
//

#define GREEDY 1
#define KNAPSACK 0
#define NON_DELIVERED_PACKAGES 2
#define DELIVERED_PACKAGES 1
#define USED_TRANSPORTS 0

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
    int totalProfitGot;
    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS: optimizeTransports(); break;
        case OPTIMIZE_PROFIT: totalProfitGot = optimizeProfit(); break;
        case OPTIMIZE_EXPRESS_DELIVERY: optimizeExpressDelivery(); break;
        case BALANCE_PACKAGES: balancePackages(); break;
    }

    bool dontGoBack = true;
    while(dontGoBack)
    {
        //int totalProfitGot = 0;
        unsigned choice;

        cout << endl
             << "|========================================================================|\n"
                "|      Non delivered packages                      [2]                   |\n"
                "|      Delivered Packages                          [1]                   |\n"
                "|      Used transports                             [0]                   |\n"
                "|========================================================================|\n";

        cout << "What do you want to see? :";
        cin >> choice;

        cout << endl; showStatistics();
        showChoseMode(choice, totalProfitGot);

        cout << endl << "Do you want to see another choice? (1 -> Yes / 0 -> No):";
        cin >> dontGoBack;
    }
}

void Optimizer::optimizeTransports() {
    restartOptimizer();

    FirstScenario firstScenario;
    vector<Transport> result =
            firstScenario.execute(allPackages, allTransports, nonDeliveredPackages);

    this->usedTransports = result;
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

int Optimizer::optimizeProfit() {
    restartOptimizer();

    unsigned algorithmSelected = chooseProfitAlgorithm();

    SecondScenario secondScenario;

    if (algorithmSelected == GREEDY)
        secondScenario.greedyProfit(allPackages, allTransports, nonDeliveredPackages);
    else if (algorithmSelected == KNAPSACK)
        secondScenario.knapsackProfit(allPackages, allTransports, nonDeliveredPackages);

    usedTransports = secondScenario.getUsedTransports();
    int totalProfit = secondScenario.getTotalProfit();

    return totalProfit;
}


void Optimizer::optimizeExpressDelivery() {
    restartOptimizer();

    ThirdScenario thirdScenario;
    vector<Transport> result =
            thirdScenario.execute(allPackages, allTransports, nonDeliveredPackages);

    this->usedTransports = result;
}

void Optimizer::balancePackages() {
    restartOptimizer();

    FourthScenario fourthScenario;
    usedTransports = fourthScenario.execute(allPackages, allTransports,nonDeliveredPackages);
}

void Optimizer::restartOptimizer() {
    usedTransports.clear();
    nonDeliveredPackages.clear();

    // makes transport.carriedPackages empty
    for (auto &transport: allTransports)
        transport.restart();
}

double Optimizer::calculateEfficiency() const {
    unsigned numDeliveredPackages = allPackages.size() - nonDeliveredPackages.size();

    double efficiency = (double) numDeliveredPackages / (double) allPackages.size();
    efficiency = round(efficiency * 10000.0) / 10000.0;

    return efficiency;
}

double Optimizer::calculateAverageTime() const {
    unsigned numDeliveredPackages = allPackages.size() - nonDeliveredPackages.size();
    unsigned sumTime = 0;

    for (auto transport: usedTransports)
        sumTime += transport.sumTime();

    double avgTime = (double) sumTime / numDeliveredPackages;

    return avgTime;
}

const vector<Package> &Optimizer::getNonDeliveredPackages() const {
    return nonDeliveredPackages;
}


void Optimizer::showStatistics() {
    cout << endl << "Used transports: " << usedTransports.size() << endl
         << "Delivered packages: " << allPackages.size() - nonDeliveredPackages.size() << endl
         << "NON delivered packages: " << nonDeliveredPackages.size() << endl
         << "Efficiency: " << calculateEfficiency() * 100 << "%" << endl;
}

void Optimizer::showTransports() const {
    cout << endl << "Transport ID" << "                     "
         << "Transports" << "                    "
         << "Number of carried packages" << endl;

    for (const auto& transport: usedTransports)
        cout << "    " << transport.getTransportId() << "       ---------------  "
             << transport.getMaxVol() << "  "
             << transport.getMaxWeight() << "  "
             << transport.getPrice() << "  ---------------  "
             << transport.getCarriedPackages().size() << endl;
}


void Optimizer::showProfit(int totalProfit) const {
    cout << "Total profit: " << totalProfit << endl << endl;
    cout << "Transport ID" << "                     "
         << "Transports" << "                     "
         << "Number of carried packages"  << "                     "
         << "Profit" << endl;

    for (const auto &transport: usedTransports)
        cout << "    " << transport.getTransportId() << "       ---------------    "
             << transport.getMaxVol() << "  "
             << transport.getMaxWeight() << "  "
             << transport.getPrice() << "  ---------------            "
             << transport.getCarriedPackages().size() << "             ------------------   "
             << transport.getProfit() << endl;
}


void Optimizer::showAvgTime() const {
    cout << "Minimum Average Time: " << calculateAverageTime() << endl << endl;
    cout << "Transport ID" << "                     "
         << "Transports" << "                    "
         << "Number of carried packages"  << endl;

    for (const auto &transport: usedTransports)
        cout << "    " << transport.getTransportId() << "       ---------------  "
             << transport.getMaxVol() << "  "
             << transport.getMaxWeight() << "  "
             << transport.getPrice() << "  ---------------  "
             << transport.getCarriedPackages().size() << endl;
}


void Optimizer::showUsedTransports(int totalProfit) const {

    switch (optimizerType)
    {
        case OPTIMIZE_TRANSPORTS: case BALANCE_PACKAGES:
            showTransports();
            break;

        case OPTIMIZE_PROFIT:
            showProfit(totalProfit);
            break;

        case OPTIMIZE_EXPRESS_DELIVERY:
            showAvgTime();
            break;
    }
}

void Optimizer::showNonDelivered() const {
    if(nonDeliveredPackages.empty())
    {
        cout << endl << "All packages were delivered!" << endl;
        return;
    }

    cout << "PackageID" << "                "
         << "Package" << "                "
         << "Order day" << "                " << endl;
    for(auto package : nonDeliveredPackages)
    {
        cout << package.getPackageId() << "                     "
             << package.getVolume() << " "
             << package.getWeight() << " "
             << package.getReward() << "                    "
             << package.getDay() << endl;
    }
}

void Optimizer::showDeliveredPackages() const {
    cout << "PackageID" << "                "
         << "Package" << "                "
         << "Order day" << "                " << endl;

    for(const auto& transport : usedTransports)
    {
        for(auto package : transport.getCarriedPackages())
        {
            cout << package.getPackageId() << "                     "
                 << package.getVolume() << " "
                 << package.getWeight() << " "
                 << package.getReward() << "                    "
                 << package.getDay() << endl;
        }
    }
}

void Optimizer::showChoseMode(unsigned choice, int totalProfitGot) const {
    switch (choice) {
        case USED_TRANSPORTS:
            if (totalProfitGot)
                showUsedTransports(totalProfitGot);

            else showUsedTransports();

            break;

        case DELIVERED_PACKAGES: showDeliveredPackages(); break;
        case NON_DELIVERED_PACKAGES: showNonDelivered(); break;
        default: break;
    }
}


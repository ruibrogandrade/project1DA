//
// Created by Rui on 04/04/2022.
//

#include <algorithm>
#include "Optimizer.h"
#include "FirstScenario.h"
#include "SecondScenario.h"
#include "ThirdScenario.h"

using namespace std;

Optimizer::Optimizer(unsigned int optimizerType, const vector<Package> &allPackages, const vector<Transport> &allTransports) {
    this->optimizerType = optimizerType;
    this->allPackages = allPackages;
    this->allTransports = allTransports;

    if(optimizerType == OPTIMIZE_EXPRESS_DELIVERY)
    {
        for(auto transport : allTransports)
        {
            transport.setExpressDelivery();
            transport.setVolumeExpress();
            transport.setWeightExpress();
        }
    }
}

void Optimizer::optimize() {
    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS: optimizeTransports(); showUsedTransports(); break;
        case OPTIMIZE_PROFIT: optimizeProfit(); showUsedTransports(); break;
        case OPTIMIZE_EXPRESS_DELIVERY: optimizeExpressDelivery(); showUsedTransports(); break;
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

    for (const auto& transport: transports) {
        if(transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
    }
}

unsigned int chooseProfitAlgorithm(){
    cout << endl <<
         "|========================================================================|\n"
         "|      Greedy Algorithm (fast, but only an approach)     [1]             |\n"
         "|      Knapsack Algorithm (precise, but so slow)         [0]             |\n"
         "|========================================================================|\n";
    while(true)
    {
        cout << "Choose an algorithm that you want to use for achieve better profit:";
        unsigned int algorithmChose;

        cin >> algorithmChose;
        if (cin.fail() || cin.peek() != '\n' || (algorithmChose != 1 && algorithmChose != 0))
        {
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

    for (auto& transport: transports)
    {
        if (transport.getCarriedPackages().empty())
            break;

        int profit = transport.calculateProfit();
        if(profit > 0)
        {
            usedTransports.push_back(transport);
            totalProfit += profit;
        }
    }
}

void Optimizer::knapsackProfit(vector<Package> &packages, vector<Transport> &transports) {
    for (auto t: transports)
    {
        auto temp = SecondScenario::knapSack(t, packages);
        int profit = (int)(temp.first-t.getPrice());
        if(profit<0) return;
        else {
            totalProfit += profit;
            for (auto rit = temp.second.rbegin(); rit != temp.second.rend(); rit++ ) {
                t.addPackage(packages[*rit]);
                packages.erase(packages.begin() + *rit);
            }
            usedTransports.push_back(t);
        }
    }
}


void Optimizer::optimizeProfit(){
    restartOptimizer();

    #define GREEDY 1
    #define KNAPSACK 0

    unsigned int algorithmSelected = chooseProfitAlgorithm();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    SecondScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    SecondScenario::sortTransport(transports);

    totalProfit = 0;

    switch (algorithmSelected)
    {
        case GREEDY:
            greedyProfit(packages, transports); break;

        case KNAPSACK:
            knapsackProfit(packages, transports); break;
    }
}

void Optimizer::optimizeExpressDelivery(){
    //TODO
    restartOptimizer();

    unsigned int time = 0;
    unsigned int counterPackages = 0;

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    FirstScenario::sortPackages(packages);

    vector<Transport> transports = allTransports; // Make a copy of the transports for don't change the original vector
    FirstScenario::sortTransport(transports);


    for(auto &transport: transports) {
        for (auto package: packages) {
            if (transport.getTime() == (8 * 3600)) break;
            if (((transport.getTime() + package.getEstimatedTime()) < (8 * 3600)) && (transport.addPackage(package))) {
                int newTime = transport.getTime() + package.getEstimatedTime();
                transport.setTime(newTime);
                counterPackages++;
            }
        }
    }
    double avgTime = 0;
    for (const auto& transport: transports) {
        if(transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
        avgTime += transport.getTime();
    }
    avgTime /= (double)counterPackages;
    //double  averageDeliveryTime = counterPackages / (transports.size() + (8 * 3600));

    cout << "Average Time " << avgTime << endl;

    /*for (auto &package: packages)
        for (auto &transport: transports)
            if ((transport.getDuration() + package.getEstimatedTime() <= 8*3600 && transport.addExpress(package))
                break;

    double avgTime = 0;
    for (const auto& transport: transports) {
        if(transport.getCarriedPackages().empty()) break;
        usedTransports.push_back(transport);
        avgTime += transport.getDuration();
    }
    avgTime /= usedTransports.size();
    cout << avgTime << endl;*/
}

void Optimizer::restartOptimizer() {
    usedTransports.clear();

    for(auto &package : allPackages)
        package.restart(); // makes package.added = false and expressDelivery = false

    for(auto &transport : allTransports) // makes transport.carriedPackages empty and expressDelivery = false
        transport.restart();
}

vector<Transport> Optimizer::getUsedTransports() const {
    return usedTransports;
}

void Optimizer::showUsedTransports() const {

    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS:
            cout << endl << "Number of transports that were used: " << usedTransports.size() << endl << endl;
            cout << "Transports                        Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------  " << transport.getCarriedPackages().size() << endl;
            break;

        case OPTIMIZE_PROFIT:
            cout << endl << "Number of transports that were used: " << usedTransports.size() << endl
             << "Total profit: " << totalProfit << endl << endl;
            cout << "Transports                        Number of carried packages                         Profit" << endl;

            for (auto transport: usedTransports)
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------               " << transport.getCarriedPackages().size()
                     << "             --------------------   " << transport.getProfit() << endl;
            break;

        case OPTIMIZE_EXPRESS_DELIVERY:
            cout << endl << "Number of transports that were used: " << usedTransports.size() << endl << endl;
            cout << "Transports                        Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------  " << transport.getCarriedPackages().size() << endl;
            break;
    }
}

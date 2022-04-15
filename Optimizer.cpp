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
        numDeliveredPackages += transport.getCarriedPackages().size();
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
            numDeliveredPackages += transport.getCarriedPackages().size();
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
            numDeliveredPackages += t.getCarriedPackages().size();
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

unsigned int sumTimeTransport(Transport &transport){
    unsigned int sumTime = 0;

    vector<Package> carriedPackages = transport.getCarriedPackages();
    for(int i = 0; i < carriedPackages.size(); i++)
    {
        for(int j = 0; j <= i; j++)
        {
            sumTime += carriedPackages[j].getEstimatedTime();
        }
    }
    return sumTime;
}

void Optimizer::optimizeExpressDelivery(){
    //TODO
    restartOptimizer();

    vector<Package> packages = allPackages; // Make a copy of the packages for don't change the original vector
    ThirdScenario::sortPackages(packages);

    for(auto package : packages)
    {
        if(!expressTransport.addExpress(package))
            break;
    }

    usedTransports.push_back(expressTransport);
    numDeliveredPackages = expressTransport.getCarriedPackages().size();

    unsigned int sumTime = sumTimeTransport(expressTransport);
    unsigned int numPackagesTransported = (unsigned) expressTransport.getCarriedPackages().size();

    avgTime = (double)sumTime / numPackagesTransported;
}

void Optimizer::restartOptimizer() {
    usedTransports.clear();

    for(auto &package : allPackages)
        package.restart(); // makes package.added = false and expressDelivery = false

    for(auto &transport : allTransports) // makes transport.carriedPackages empty and expressDelivery = false
        transport.restart();

    totalProfit = 0; numDeliveredPackages = 0; avgTime = 0;
}

vector<Transport> Optimizer::getUsedTransports() const {
    return usedTransports;
}

void Optimizer::showUsedTransports() const {

    switch (optimizerType) {
        case OPTIMIZE_TRANSPORTS:
            cout << endl << "Used transports: " << usedTransports.size() << endl
            << "Delivered packages: "<< numDeliveredPackages << endl
            << "NON delivered packages: " << allPackages.size() - numDeliveredPackages << endl << endl;
            cout << "Transports                        Number of carried packages" << endl;

            for (const auto &transport: usedTransports)
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------  " << transport.getCarriedPackages().size() << endl;
            break;

        case OPTIMIZE_PROFIT:
            cout << endl << "Used transports: " << usedTransports.size() << endl
            << "Delivered packages: "<< numDeliveredPackages << endl
            << "NON delivered packages: " << allPackages.size() - numDeliveredPackages << endl
            << "Total profit: " << totalProfit << endl << endl;
            cout << "Transports                        Number of carried packages                         Profit" << endl;

            for (auto transport: usedTransports)
                cout << transport.getMaxVol() << "  " << transport.getMaxWeight() << "  " << transport.getPrice()
                     << "  ---------------               " << transport.getCarriedPackages().size()
                     << "             --------------------   " << transport.getProfit() << endl;
            break;

        case OPTIMIZE_EXPRESS_DELIVERY:
            cout << endl << "Used transports: " << usedTransports.size() << endl
                    << "Delivered packages: "<< numDeliveredPackages << endl
                    << "NON delivered packages: " << allPackages.size() - numDeliveredPackages << endl
                    << "Minimum Average Time: " << avgTime << endl << endl;
            cout << "Transports                           Number of carried packages" << endl;


            cout << "Express Transport" << "   ---------------  "
                << expressTransport.getCarriedPackages().size() << endl;
            break;
    }
}


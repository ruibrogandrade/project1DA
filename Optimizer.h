//
// Created by Rui on 04/04/2022.
//

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Package.h"
#include "Transport.h"
#include <vector>
#include <map>
#include <utility>

using namespace std;

#define OPTIMIZE_TRANSPORTS 1
#define OPTIMIZE_PROFIT 2
#define OPTIMIZE_EXPRESS_DELIVERY 3
#define EXIT 0

class Optimizer {
private:
    //class' attributes
    //vector<map<Package,bool>> allPackages; // This map tells if package has already added or hasn't;
    //vector<map<Transport,bool>> allTransports; // This map tells if transport has already added or hasn't;
    vector<Transport> usedTransports;
    vector<Transport> allTransports;
    vector<Package> allPackages;
    unsigned int optimizerType = 0;
    int totalProfit = 0;

private:
    //private methods. They are only used as auxiliary functions in the public optimize methods
    void restartOptimizer();
    void optimizeTransports();
    void optimizeProfit();
    void optimizeExpressDelivery();
    void knapsackProfit(vector<Package> &packages, vector<Transport> &transports);
    void greedyProfit(vector<Package> &packages, vector<Transport> &transports);

public:
    Optimizer()= default;
    Optimizer(unsigned int optimizerType, const vector<Package> &allPackages, const vector<Transport> &allTransports);
    void optimize();
    vector<Transport> getUsedTransports() const;
    void showUsedTransports() const;
};

#endif //OPTIMIZER_H

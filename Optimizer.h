//
// Created by Rui on 04/04/2022.
//

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#define EXIT 0
#define OPTIMIZE_TRANSPORTS 1
#define OPTIMIZE_PROFIT 2
#define OPTIMIZE_EXPRESS_DELIVERY 3
#define BALANCE_PACKAGES 4

#include "Package.h"
#include "Transport.h"
#include <vector>
#include <map>
#include <utility>

using namespace std;

class Optimizer {
private:
    vector<Transport> usedTransports;
    vector<Transport> allTransports;
    vector<Package> allPackages;
    unsigned optimizerType = 0, numDeliveredPackages = 0;
    int totalProfit = 0;
    double avgTime = 0;
    double efficiency = 0;

private:
    /**
     * Clears all the data structures
     */
    void restartOptimizer();
    /**
     * Algorithm that minimizes the number of Transports needed for a certain number of Packages (Greedy)
     */
    void optimizeTransports();
    /**
     * 2 Algorithms that maximizes the profit of delivering packages (Greedy and Dynamic Programming(knapsack)
     */
    void optimizeProfit();
    /**
     * Algorithm that minimizes the average time needed to deliver packages
     */
    void optimizeExpressDelivery();
    /**
     * Algorithm that distributes the packages equally amongst all the transports
     */
    void balancePackages();
    /**
     * Shows the transports that were used
     */
    void showUsedTransports() const;
    /**
     * Calculates in percentage how many packages were used
     */
    void calculateEfficiency();
    /**
     * Calculates the average time of the delivery of the packages
     */
    void calculateAverageTime();

public:
    /**
     * Empty Constructor
     */
    Optimizer() = default;
    /**
     * Constructor for getting the data needed for the algorithms and knowing which ones to use
     * @param optimizerType selects wich Algorithms are ggoing to be used
     * @param allPackages a vector that contains all Packages
     * @param allTransports a vector that contains all Transports
     */
    Optimizer(unsigned optimizerType, const vector<Package> &allPackages, const vector<Transport> &allTransports);
    /**
     *  Chooses what is going to be optimized
     */
    void optimize();
};

#endif //OPTIMIZER_H

//
// Created by gdrp7 on 10/04/2022.
//

#ifndef MAIN_CPP_SECONDSCENARIO_H
#define MAIN_CPP_SECONDSCENARIO_H

#include <set>
#include "Package.h"
#include "Transport.h"

class SecondScenario {
private:
    int totalProfit = 0;
    vector<Transport> usedTransports{};

    /**
     * Compare packages according to their reward, weight, and volume.
     * Since we want to maximize the value of total profit, the value "reward"
     * of the packages as more influence in the comparison.
     * @param p1 - package 1
     * @param p2 - package 2
     * @return - (package 1 < package 2)? (bool)
     */
    static bool comparePackages(const Package &p1, const Package &p2);

    /**
     * Compare transports according to their deployment price, maximum weight,
     * and maximum volume. Since we want to maximize the value of total profit,
     * the value "price" has more influence in the comparison.
     * @param t1 - transport 1
     * @param t2 - transport 2
     * @return - (transport 1 < transport 2)? (bool)
     */
    static bool compareTransports(const Transport &t1, const Transport &t2);

    /**
     * An implementation of a multidimensional 0-1 knapsack, executed with dynamic programming,
     * that builds a matrix to determine the maximum amount of profit in one transport
     * with the given packages.
     * @param t - transport which we want the profit maximized
     * @param packages - a vector that has all the packages available for transportation
     * @return
     */
    static pair<unsigned, set<unsigned>> knapsack(Transport &t, vector<Package> &packages);

public:
    /**
     * Returns the total profit after trying to maximize it.
     * @return int - maximum profit.
     */
    int getTotalProfit() const;

    /**
     * Returns the transports that were used after trying to optimize the profit.
     * @return vector<Transport> - Transports that were used.
     */
    const vector<Transport> &getUsedTransports() const;

    /**
     * Executes the second scenario using the private function "knapsack" for each
     * given transport, until the profit calculation is negative.
     * @param packages - a vector that has all the packages that we want delivered
     * @param transports - a vector that has all transports available for deployment
     */
    void knapsackProfit(vector<Package> packages, vector<Transport> transports, vector<Package> &nonDeliveredPackages);

    /**
     * Executes the bin-packing algorithm after sorting by descending order of packages
     * and after the sort the transports by ascending order of transports.
     * This function achieves only an approach to the actual optimal profit
     * but is much faster than the knapsack algorithm.
     * @param packages - all packages stored from the database.
     * @param transports - all transports stored from the database.
     */
    void greedyProfit(vector<Package> packages, vector<Transport> transports, vector<Package> &nonDeliveredPackages);
};

#endif //MAIN_CPP_SECONDSCENARIO_H

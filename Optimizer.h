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
    //vector<map<Package,bool>> allPackages; // This map tells if package has already visited or hasn't;
    //vector<map<Transport,bool>> allTransports; // This map tells if transport has already visited or hasn't;
    vector<Transport> usedTransports;
    vector<Transport> allTransports;
    vector<Package> allPackages;
    unsigned int optimizerType;

private:
    //private methods. They are only used as auxiliary functions in the public optimize methods
    static bool comparePackages(const Package& p1, const Package& p2);
    static bool compareTransports(const Transport& t1, const Transport& t2);
    vector<Package> sortPackages(vector<Package> &packages);
    vector<Transport> sortTransport(vector<Transport> &transports);

public:
    Optimizer(){};
    Optimizer(unsigned int optimizerType, const vector<Package> &allPackages, const vector<Transport> &allTransports);
    void optimizeTransports();
    void optimizeProfit();
    void optimizeExpressDelivery();
    void optimize();
    vector<Transport> getUsedTransports() const;
};

#endif //OPTIMIZER_H

//
// Created by gdrp7 on 10/04/2022.
//

#include <algorithm>
#include "SecondScenario.h"

bool SecondScenario::comparePackages(const Package &p1, const Package &p2) {
    return p1.getReward()>p2.getReward();
}

bool SecondScenario::compareTransports(const Transport &t1, const Transport &t2) {
    return t1.getPrice()<t2.getPrice();
}

vector<Package> SecondScenario::sortPackages(vector<Package> &packages) {
    sort(packages.begin(), packages.end(), comparePackages);
    return packages;
}

vector<Transport> SecondScenario::sortTransport(vector<Transport> &transports) {
    sort(transports.begin(), transports.end(), compareTransports);
    return transports;
}

Transport SecondScenario::knapSack(Transport& t, vector<Package> &p) {

    unsigned int W = t.getMaxWeight(), V = t.getMaxVol(),
        n = p.size();

    vector<vector<vector<int>>> K(n+1, vector<vector<int>>(W+1, vector<int>(V+1)));
    // We know we are always using the the current row or
    // the previous row of the array/vector . Thereby we can
    // improve it further by using a 2D array but with only
    // 2 rows i%2 will be giving the index inside the bounds
    // of 2d array K

    for (int i = 0; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            for (int v = 0; v <= V; v++) {
                if (i == 0 || w == 0 || v == 0)
                    K[i][w][v] = 0;
                else if (p[i - 1].getWeight() <= w && p[i -1].getVolume() <= v)
                    if (p[i - 1].getReward() + K[i - 1][w - p[i - 1].getWeight()][v - p[i - 1].getVolume()] <= K[i - 1][w][v])
                        K[i][w][v] = K[i - 1][w][v];
                    else K[i][w][v] = p[i - 1].getReward() + K[i - 1][w - p[i - 1].getWeight()][v - p[i - 1].getVolume()];
                else
                    K[i][w][v] = K[i - 1][w][v];
            }
        }
    cout << K[n][W][V] << endl;
    return K[n][W][V];
}

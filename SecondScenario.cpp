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

void SecondScenario::knapSack(Transport& t, vector<Package> &p) {
    //TODO
    unsigned int maxWeight = t.getMaxWeight(),
        maxVol = t.getMaxVol(),
        size = p.size();

    // Three-dimensional matrix with dimension 2*maxWeight*maxVol
    // that stores a set of Packages and an integer that is equal
    // to the sum of all the rewards on the set
    vector<vector<vector<pair<unsigned int, set<Package*>>>>> matrix
        (2, vector<vector<pair<unsigned int, set<Package*>>>>
        (maxWeight + 1, vector<pair<unsigned int, set<Package*>>>(maxVol + 1)));

    for (int index = 0; index <= size; index++)
        for (int weight = 0; weight <= maxWeight; weight++)
            for (int volume = 0; volume <= maxVol; volume++)

                // Basic cases of the matrix
                if (index == 0 || weight == 0 || volume == 0) continue;

                // Calculates if package of index (i-1) fits in the
                // given weight and volume
                else if (p[index - 1].getWeight() > weight ||
                         p[index - 1].getVolume() > volume) {

                    // Use pair in the previous position in the matrix
                    matrix[index % 2][weight][volume] =
                            matrix[(index - 1) % 2][weight][volume];
                } else {
                    // Max value:

                    // Calculation of the new pair
                    // (combination between a pair in the matrix and one package from the vector)
                    pair<unsigned int, set<Package*>> newPair = matrix[(index - 1) % 2]
                    [weight - p[index - 1].getWeight()]
                    [volume - p[index - 1].getVolume()];

                    // Adds package of index (i-1) to the new pair, if it's capable
                    // then actualizes the total value of profit
                    if (newPair.second.insert(&p[index - 1]).second)
                        newPair.first += p[index - 1].getReward();

                    // Stores the new pair if it's profits is better,
                    // or the pair in the previous position otherwise
                    matrix[index % 2][weight][volume] =
                            (matrix[(index - 1) % 2][weight][volume].first > newPair.first) ?
                            matrix[(index - 1) % 2][weight][volume] : newPair;
                }

    // Value with the maximum profit for the given transport
    cout << matrix[size % 2][maxWeight][maxVol].first << endl;
}

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

    unsigned int
        maxWeight = t.getMaxWeight(),
        maxVol = t.getMaxVol(),
        size = p.size();

    vector<vector<vector<int>>> matrix(2, vector<vector<int>>(maxWeight + 1, vector<int>(maxVol + 1)));

    for (int index = 0; index <= size; index++)
        for (int weight = 0; weight <= maxWeight; weight++)
            for (int volume = 0; volume <= maxVol; volume++)

                // Initialize basic cases of the matrix
                if (index == 0 || weight == 0 || volume == 0)
                    matrix[index % 2][weight][volume] = 0;

                // Calculates if package of index (i-1) fits in the
                // given weight and volume
                else if (p[index - 1].getWeight() <=
                         weight && p[index - 1].getVolume() <= volume)

                    // Calculation of max value:
                    // Compares if we will use the value stored in the previous position
                    // or a new value (result of a combination between 2 values in the matrix)
                    if (p[(index - 1) % 2].getReward() +
                        matrix[(index - 1) % 2][weight - p[index - 1].getWeight()][volume - p[index - 1].getVolume()] <=
                        matrix[(index - 1) % 2][weight][volume])

                        // Use previous value
                        matrix[index % 2][weight][volume] =
                                matrix[(index - 1) % 2][weight][volume];

                    // Use a new combination of values
                    else matrix[index % 2][weight][volume] =
                            p[index - 1].getReward() + matrix[(index - 1) % 2][weight - p[index - 1].getWeight()][volume - p[index - 1].getVolume()];

                // Use previous value
                else matrix[index % 2][weight][volume] =
                             matrix[(index - 1) % 2][weight][volume];

    // Value with the maximum profit for the given transport
    cout << matrix[size % 2][maxWeight][maxVol] << endl;
    return matrix[size % 2][maxWeight][maxVol];
}
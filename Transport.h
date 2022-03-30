//
// Created by gdrp7 on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_TRANSPORT_H
#define URBAN_LOGISTICS_TRANSPORT_H


class Transport {
private:
    unsigned int maxVol;
    unsigned int maxWeight;
    unsigned int price;
public:
    Transport(unsigned int maxVol, unsigned int maxWeight, unsigned int price);
    unsigned int getMaxWeight() const;
    void setMaxWeight(unsigned int maxWeight);
    unsigned int getMaxVol() const;
    void setMaxVol(unsigned int maxVol);
    unsigned int getPrice() const;
    void setPrice(unsigned int price);
};


#endif //URBAN_LOGISTICS_TRANSPORT_H

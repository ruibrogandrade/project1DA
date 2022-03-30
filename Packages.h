//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_PACKAGES_H
#define URBAN_LOGISTICS_PACKAGES_H


class Packages {
private:
    int volume;
    int weight;
    int reward;
    int duration;
    bool ExpressDelivery;
public:
    int getVolume() const;
    void setVolume(int volume);
    int getWeight() const;
    void setWeight(int weight);
    int getReward() const;
    void setReward(int reward);
    int getDuration() const;
    void setDuration(int duration);
    bool isExpressDelivery() const;
    void setExpressDelivery(bool expressDelivery);
};


#endif //URBAN_LOGISTICS_PACKAGES_H

//
// Created by Rui on 30/03/2022.
//

#ifndef URBAN_LOGISTICS_PACKAGES_H
#define URBAN_LOGISTICS_PACKAGES_H


class Packages {
private:
    unsigned int volume;
    unsigned int weight;
    unsigned int reward;
    unsigned int duration;
    bool ExpressDelivery;
public:
    Packages(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int duration,
             bool expressDelivery);

    unsigned int getVolume() const;
    void setVolume(unsigned int volume);
    unsigned int getWeight() const;
    void setWeight(unsigned int weight);
    unsigned int getReward() const;
    void setReward(unsigned int reward);
    unsigned int getDuration() const;
    void setDuration(unsigned int duration);
    bool isExpressDelivery() const;
    void setExpressDelivery(bool expressDelivery);
};


#endif //URBAN_LOGISTICS_PACKAGES_H

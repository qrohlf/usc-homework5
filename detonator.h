#ifndef DETONATOR_H
#define DETONATOR_H
#include "enemy.h"

/**
  @brief A type of Enemy which will wait several seconds before charging forward and exploding
  **/
class Detonator : public Enemy
{
public:
    Detonator(QPoint start_location, int ticks_until_charge);
    virtual void move(QPoint player_loc);
    virtual Enemy* shoot(QPoint player_loc);
    std::string getType();
protected:
    ///Keep track of the number of ticks before the Detonator will detonate (-100 means immediate detonation)
    int ticks_until_charge;
    ///Keep track of the number of ticks which have elapsed
    int ticks;
    //Keep track of whether the Detonator is currently in the process of detonating
    bool shootbool;
    //Keep track of how many shots the Detonator has fired
    int shotcounter;
};

#endif // DETONATOR_H

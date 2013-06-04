#ifndef KAMIKAZE_H
#define KAMIKAZE_H
#include "fighter.h"

/**
  @brief Fighter Enemy whose main way of causing damage is to collide with the Player
  **/
class Kamikaze : public Fighter
{
public:
    Kamikaze(QPoint start_location, int ticks_until_charge, bool respawn=true);
    virtual void move(QPoint player_loc);
    virtual Enemy* shoot(QPoint player_loc);
protected:
    ///The number of ticks until the Kamikaze will charge
    int ticks_until_charge;
    ///The number of ticks between each charge
    int ticks_until_charge_original;
    ///Keep track of the elapsed ticks
    int ticks;
    ///Keep track of the spawn location
    QPoint start_location;
    ///Flag to track whether to respawn after exiting the screen
    bool respawn;
};

#endif // KAMIKAZE_H

#ifndef SEEKER_H
#define SEEKER_H
#include "enemy.h"

/**
  @brief An Enemy which homes in on the Player to cause damage
  **/
class Seeker : public Enemy
{
public:
    Seeker(QPoint start_location, bool randomstart = false);
    virtual void move(QPoint player_loc);
    std::string getType();
    virtual Enemy* shoot(QPoint player_loc);
protected:
    ///Where the Seeker should return to after the seek cycle is over
    QPoint home;
    ///Keep track of the cycle
    int counter;
    ///The Seeker's direction of travel
    QPoint direction;
};

#endif // SEEKER_H

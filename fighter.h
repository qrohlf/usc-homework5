#ifndef FIGHTER_H
#define FIGHTER_H
#include "enemy.h"

/**
  @brief A type of Enemy which flies in a square pattern while lobbing low-damage bullets
  **/
class Fighter : public Enemy
{
public:
    Fighter(QPoint start_location);
    virtual void move(QPoint player_loc);
    std::string getType();
    virtual Enemy* shoot(QPoint player_loc);
protected:
    ///Rolling counter to keep track of when to shoot
    int counter;
    ///Randomized threshold to keep track of when to shoot
    int shootpoint;
};

#endif // FIGHTER_H

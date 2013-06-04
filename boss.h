#ifndef BOSS_H
#define BOSS_H
#include "enemy.h"

/**
  @brief A simple boss Enemy which tracks the player's x coordinate

  the Boss shoots aimed (but non-homing) missiles
  **/
class Boss : public Enemy
{
public:
    Boss(QPoint start_location);
    void move(QPoint player_loc);
    std::string getType();
    virtual Enemy* shoot(QPoint player_loc);
protected:
    /// A counter to keep track of where the Boss is in its firing cycle
    int counter;

};

#endif // BOSS_H

#ifndef HEAVY_H
#define HEAVY_H
#include "enemy.h"

/**
  @brief Durable Enemy which fires powerful homing missiles
  **/
class Heavy : public Enemy
{
public:
    Heavy(QPoint start_location);
    void move(QPoint player_loc);
    std::string getType();
    virtual Enemy* shoot(QPoint player_loc);
private:
    ///counter to keep track of when to fire/move
    int counter;
};

#endif // HEAVY_H

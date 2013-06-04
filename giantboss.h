#ifndef GIANTBOSS_H
#define GIANTBOSS_H
#include "enemy.h"

/**
  @brief Huge boss Enemy which is very hard to kill

  This Enemy has the distinction of actually shooting other types of Enemy rather than just Bullet objects
  **/
class GiantBoss : public Enemy
{
public:
    GiantBoss(QPoint start_location);
    void move(QPoint player_loc);
    std::string getType();
    virtual Enemy* shoot(QPoint player_loc);
private:
    ///Rolling counter to keep track of where the GiantBoss is in the cycle
    int counter;
};

#endif // GIANTBOSS_H

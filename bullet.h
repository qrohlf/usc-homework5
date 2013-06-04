#ifndef BULLET_H
#define BULLET_H
#include "enemy.h"

/**
  @brief A Bullet which travels based on the direction assigned to it. Capable of homing towards the player
  **/
class Bullet : public Enemy
{
public:
    Bullet(QPoint start_location, int damage, QPoint direction);
    void move(QPoint player_loc);
    std::string getType();
    void setHoming(bool ishoming);
protected:
    ///A flag which determines if the Bullet will exhibit homing behavior
    bool homing;
    ///Used to keep track of the Bullet's direction of travel
    QPoint direction;
};

#endif // BULLET_H

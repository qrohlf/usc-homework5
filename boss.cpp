#include "boss.h"
#include <cmath>
#include "bullet.h"

/**
  Construct a new Boss Enemy at the given location
  @param start_location     QPoint containing the starting location
  **/
Boss::Boss(QPoint start_location) :
    //Initialize a boss enemy at start location with 15 points of health, rewarding 50 points per hit, and with a boss1 pixmap
    Enemy(start_location, 150, 50, 100, QImage(":/ships/res/boss1.png"))
{
}

/**
  Move the Boss to track the player's movement on the X axis
  @param player_loc     QPoint containing the player's location
  **/
void Boss::move(QPoint player_loc) {
    int dx = location.x()-player_loc.x();
    if (dx > 20){
        moveLeft(1);
    } else if (dx < -20) {
        moveRight(1);
    }
}

std::string Boss::getType() {
    return "Boss";
}

/**
  Shoot an aimed (but not homing) missile
  @param player_loc     QPoint containing the player's location
  **/
Enemy* Boss::shoot(QPoint player_loc) {
    counter = (counter+1)%200; //every tick on the counter is 10ms. Shoot every 2.5 seconds
    if (counter == 0 || counter == 20) {
        QPoint direction = location-player_loc;
        direction.setX(8*direction.x()/direction.y());
        direction.setY(8);
        Bullet* b = new Bullet(location, 30, direction);
        b->setImage(QImage(":/ships/res/bigbullet.png"));
        return b;
    }
    else return NULL;
}




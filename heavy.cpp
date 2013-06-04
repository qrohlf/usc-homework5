#include "heavy.h"
#include "bullet.h"
/**
  Construct a new heavy
  @param start_location the Heavy's starting location
  **/
Heavy::Heavy(QPoint start_location) :
    Enemy(start_location, 300, 5, 400, QImage(":/ships/res/heavy.png"))
{
}

/**
  Move the heavy. (actually just rumble back and forth)
  @param player_loc unused
  **/
void Heavy::move(QPoint player_loc) {
    if(counter%4==0) {
        (counter>100)?moveLeft(1):moveRight(1);
    }
}

std::string Heavy::getType() {
    return "Heavy";
}

/**
  Give the heavy an opportunity to shoot
  @param player_loc the Player's location
  @return NULL if not shooting, otherwise a homing missile Bullet*
  **/
Enemy* Heavy::shoot(QPoint player_loc) {
    counter = (counter+1)%200; //every tick on the counter is 10ms. Shoot every 2.5 seconds
    if (counter == 0 || counter == 1) {
        QPoint direction = location-player_loc;
        direction.setX(4*direction.x()/direction.y());
        direction.setY(4);
        Bullet* b = new Bullet(location+QPoint((counter==0)?25:-25, 0), 20, direction);
        b->setImage(QImage(":/ships/res/missile.png"));
        b->setHoming(true);
        return b;
    }
    else return NULL;
}

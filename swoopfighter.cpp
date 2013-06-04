#include "swoopfighter.h"
#include "fighter.h"
#include "bullet.h"
/**
  Construct a new Swoopfighter
  @param start_location
  @param ticks_until_charge the number of ticks (1 tick = 10ms) before the fighter starts its swoop
  **/
Swoopfighter::Swoopfighter(QPoint start_location, int ticks_until_charge):
    Fighter(start_location),
    ticks_until_charge(ticks_until_charge),
    ticks(ticks_until_charge),
    start_location(start_location),
    swoop(false)
{
    health = 75;
    setImage(QImage(":/ships/res/fighter3.png"));
}

/**
  move the Swoopfighter
  @param player_loc the player's location
  **/
void Swoopfighter::move(QPoint player_loc) {
    ticks--;
    if(swoop) {
        if (ticks < 200) {
            moveUp(1);
            if (start_location.x()-location.x()>6) moveRight(3);
            if (start_location.x()-location.x()<-6) moveLeft(3);
        }
        if (ticks >= 200) {
            moveDown(1);
            if (player_loc.x()-location.x()>6) moveRight(3);
            if (player_loc.x()-location.x()<-6) moveLeft(3);
        }
        if (ticks == 0) {
            ticks = 400;
            swoop = false;
        }

    } else {
        Fighter::move(player_loc);
        if (ticks==0) {
            ticks = 400;
            swoop = true;
        }
    }
}

/**
  give the Swoopfighter an opportunity to shoot.
  It will shoot normally in fighter mode, and fire a heavy volley in swoop mode
  @return Bullet* or NULL
  **/
Enemy* Swoopfighter::shoot(QPoint player_loc) {
    if (!swoop) return Fighter::shoot(player_loc);
    else if (ticks%20==0) return new Bullet(location, 5, QPoint(0, 4));
    else return NULL;
}

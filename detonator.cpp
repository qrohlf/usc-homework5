#include "detonator.h"
#include "bullet.h"

/**
  Construct a new Detonator Enemy
  @param start_location         The starting location for the Detonator
  @param ticks_until_charge     The number of ticks (1 tick=10ms) until the
                                Detonator charges
  **/
Detonator::Detonator(QPoint start_location, int ticks_until_charge):
    Enemy(start_location, 1, 45, 100, QImage(":/ships/res/detonator.png")),
    ticks_until_charge(ticks_until_charge),
    ticks(0),
    shotcounter(0),
    shootbool(false)
{
}

/**
  Move the Detonator based on its movement rules
  @param player_loc     A QPoint containing the player's location
  **/
void Detonator::move(QPoint player_loc) {
    ticks++;
    if (ticks<ticks_until_charge) {
        if((ticks/5)%2) moveLeft(1);
        else moveRight(1);
    } else if (ticks-ticks_until_charge < 100) {
        bool wiggle = (ticks/5)%2;
        if (wiggle) {
            moveLeft(3);
        } else {
            moveRight(3);
        }
    } else if (location.y()<400){
        location+=QPoint(0, 6);
    }
}

std::string Detonator::getType() {
    return "Detonator";
}

/**
  Give the Detonator an opportunity to shoot
  @param player_loc A QPoint containing the player's location
  @return           A Bullet object if the detonator is detonating, NULL otherwise
  **/
Enemy* Detonator::shoot(QPoint player_loc) {
    if (location.y() >= 400) {
        shotcounter++;
        switch(shotcounter) {
        case 1:
            return new Bullet(location, 15, QPoint(-4, 1));
            break;
        case 2:
            return new Bullet(location, 15, QPoint(-3, 3));
            break;
        case 3:
            return new Bullet(location, 15, QPoint(-1, 4));
            break;
        case 4:
            return new Bullet(location, 15, QPoint(1, 4));
            break;
        case 5:
            return new Bullet(location, 15, QPoint(3, 3));
            break;
        case 6:
            return new Bullet(location, 15, QPoint(4, 1));
            break;
        case 7:
            health = 0;
            return NULL;
            break;
        }
    } else return NULL;
}

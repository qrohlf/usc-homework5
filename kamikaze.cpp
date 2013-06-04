#include "kamikaze.h"
#include "fighter.h"
#include <iostream>

/**
  Construct a new Kamikaze Fighter
  @param start_location
  @param ticks_until_charge The number of ticks until this Kamikaze should charge
  @param whether the Kamikaze should respawn after going offscreen (default true)
  **/
Kamikaze::Kamikaze(QPoint start_location, int ticks_until_charge, bool respawn):
    Fighter(start_location),
    ticks_until_charge(ticks_until_charge),
    ticks_until_charge_original(ticks_until_charge),
    ticks(0),
    start_location(start_location),
    respawn(respawn)
{
    setImage(QImage(":/ships/res/kamikaze_noflame.png"));
}

/**
  Move the Kamikaze
  @param player_loc unused
  **/
void Kamikaze::move(QPoint player_loc) {
    ticks++;
    if (ticks<ticks_until_charge) {
        Fighter::move(player_loc);
    } else if (ticks==ticks_until_charge) {
        setImage(QImage(":/ships/res/kamikaze_flame.png"));
    } else if (ticks-ticks_until_charge < 100) {
        bool wiggle = (ticks/5)%2;
        if (wiggle) {
            moveLeft(2);
        } else {
            moveRight(2);
        }
    } else {
        location+=QPoint(0, 8);
    }
    if (location.x()<=0 || location.y() <=0 || location.x()>=700 || location.y()>=700) {
        if (respawn) {
            ticks = 0;
            ticks_until_charge = ticks_until_charge_original;
            location = start_location;
            setImage(QImage(":/ships/res/kamikaze_noflame.png"));
        } else {
            health = 0;
        }
    }
}

/**
  Shoot like a fighter if behaving like a fighter, otherwise do nothing
  @return NULL if kamikaze-diving, return Fighter::shoot() otherwise
  **/
Enemy* Kamikaze::shoot(QPoint player_loc) {
    if (ticks<ticks_until_charge) {
        return Fighter::shoot(player_loc);
    } else {
        return NULL;
    }
}

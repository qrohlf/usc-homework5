#include "fighter.h"
#include "bullet.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

/**
  Construct a new Fighter Enemy
  @param start_location The starting location for the Fighter
  **/
Fighter::Fighter(QPoint start_location) :
    Enemy(start_location, 30, 0, 10, QImage(":/ships/res/fighter1.png"))
{
    shootpoint = rand()%200;
}

/**
  Move the Fighter according to its internal timer
  @param player_loc The player's location
  **/
void Fighter::move(QPoint player_loc) {
    counter = (counter+1)%200; //every tick on the counter is 10ms.
    if (counter%2==1) {  //move ever 20ms rather than every 10ms
        switch(counter/50) {
        case 0:
            moveDown(1);
            break;
        case 1:
            moveRight(1);
            break;
        case 2:
            moveUp(1);
            break;
        case 3:
            moveLeft(1);
            break;
        }
    }
    if (counter==0) {
        shootpoint = rand()%200;
    }
}

std::string Fighter::getType() {
    return "Fighter";
}

/**
  Give the fighter the opportunity to shoot a Bullet.
  The fighter will shoot once every 200 ticks (2000ms)
  @return a Bullet* if shooting, NULL otherwise
  **/
Enemy* Fighter::shoot(QPoint player_loc) {
    if (counter == shootpoint) return new Bullet(location, 5, QPoint(0, 4));
    else return NULL;
}

#include "lazerfighter.h"
#include "bullet.h"
#include <iostream>
/**
  Construct a new LazerFighter
  @param start_location
  **/
LazerFighter::LazerFighter(QPoint start_location):
    Fighter(start_location)
{
    int r = rand()%800;
    std::cout << "random counter init: " << r << std::endl;
    ticks = r;
    setImage(QImage(":/ships/res/lazerfighter.png"));
}

/**
  Fire a stream of lazers every 1000ms
  @param player_loc unused
  @return Bullet* or NULL
  **/
Enemy* LazerFighter::shoot(QPoint player_loc) {
    ticks = (ticks+1)%200;
    if (ticks<100) {
        Bullet* b = new Bullet(location, 1, QPoint(0, 10));
        b->setImage(QImage(":/ships/res/lazer.png"));
        return b;
    } else return NULL;
}

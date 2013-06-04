#include "bullet.h"

/**
  Construct a new Bullet enemy
  @param start_location     the starting location for the Bullet
  @param damage             how much damage the Bullet deals
  @param direction          QPoint containing the direction of the Bullet
  **/
Bullet::Bullet(QPoint start_location, int damage, QPoint direction) :
    Enemy(start_location, damage, 0, 0, QImage(":/ships/res/bullet_standard.png")),
    direction(direction),
    homing(false)
{
}

/**
  Move the Bullet according to its direction and configuration
  @param player_loc     QPoint containing the player's location
  **/
void Bullet::move(QPoint player_loc) {
    if (homing) {
        QPoint diff = location-player_loc;
        if (diff.y()<0) direction.setX((diff.x()*direction.y())/diff.y());
        if (direction.x()>5) direction.setX(5);
        if (direction.x()< -5) direction.setX(-5);
    }
    location+=direction;
    if (location.x()<=0 || location.y() <=0 || location.x()>=700 || location.y()>=700) {
        health = 0;
    }
}

std::string Bullet::getType() {
    return "Bullet";
}

/**
  Set whether the Bullet will adjust its direction to follow the player's movements
  @param ishoming
  **/
void Bullet::setHoming(bool ishoming) {
    homing = ishoming;
}

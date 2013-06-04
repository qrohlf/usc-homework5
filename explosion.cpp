#include "explosion.h"

/**
  A class used to replace an Enemy with an Explosion.
  Explosions are ignored by the collision and bullet-tracking methods and cannot cause or take damage.
  They die after @param duration
  @param starting_location
  **/
Explosion::Explosion(QPoint starting_location, int duration) :
    Enemy(starting_location, 1, 0, 0, QImage(":/ships/res/explosion_1.png")),
    explosion_1(QImage(":/ships/res/explosion_1.png")),
    explosion_2(QImage(":/ships/res/explosion_2.png")),
    explosion_3(QImage(":/ships/res/explosion_3.png")),
    explosion_4(QImage(":/ships/res/explosion_4.png")),
    ms_left(duration)
{
}

/**
  Increment the Explosion's animation
  @param player_loc The player's location
  **/
void Explosion::move(QPoint player_loc) {
    ms_left -= 10;
    switch ((ms_left/100)%4) {
    case 0:
        setImage(explosion_1);
        break;
    case 1:
        setImage(explosion_2);
        break;
    case 2:
        setImage(explosion_3);
        break;
    case 3:
        setImage(explosion_4);
        break;
    }
    if (ms_left <= 0) health = 0;
}

/**
  Override of Enemy::getLocation() to account for the scale factor of the explosion.
  @return location
  **/
QPoint Explosion::getLocation()
{
    return location-QPoint(w_scale/2, h_scale/2);
}

/**
  Override of Enemy::getImage() to account for the scale factor of the explosion
  @return scaled explosion image
  **/
QImage Explosion::getImage() {
    return image.scaled(w_scale, h_scale);
}

/**
  Set the scale factor of the explosion
  @param width  desired width
  @param height desired height
  **/
void Explosion::setScale(int width, int height) {
    w_scale = width;
    h_scale = height;
}

std::string Explosion::getType() {
    return "Explosion";
}

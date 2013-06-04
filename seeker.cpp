#include "seeker.h"
#include "bullet.h"
#include <iostream>
/**
  Construct a new Seeker
  @param start_location
  @param randomstart        Whether to start the swoop randomly or in unison with other Seekers
  **/
Seeker::Seeker(QPoint start_location, bool randomstart) :
    Enemy(start_location, 75, 5, 10, QImage(":/ships/res/fighter2.png")),
    home(start_location),
    counter(0)
{
    int r = rand()%800;
    std::cout << "random counter init: " << r << std::endl;
    if (randomstart) counter = r; //randomise the cycle
}

/**
  Move the seeker
  @param player_loc the Player location
  **/
void Seeker::move(QPoint player_loc) {
    counter = (counter+1)%800; //every tick on the counter is 10ms.
    QPoint dest;
    if (counter < 400) {
        dest = player_loc;
    } else {
        dest = home;
    }
    QPoint diff = location-dest;
    if (diff.y()>0) {
        direction.setY(-1);
    } else if (diff.y()<0) {
        direction.setY(1);
    } else {
        direction.setY(0);
    }
    if (diff.x()>6) direction.setX(-2);
    else if (diff.x()< -6) direction.setX(2);
    else direction.setX(0);
    location+=direction;
    if (location.y()<0+image.height()/2) location.setY(0+image.height()/2);
    if (location.y()>700-image.height()/2) location.setY(700-image.height()/2);
    if (location.x()>700) location.setX(700);
    if (location.x()<0) location.setX(0);

}

std::string Seeker::getType() {
    return "Seeker";
}

/**
  Give the seeker an opportunity to shoot
  @return Bullet* if shooting, NULL otherwise
  **/
Enemy* Seeker::shoot(QPoint player_loc) {
    if (counter/2 == rand()%300) return new Bullet(location, 5, QPoint(0, 4));
    else return NULL;
}

#include "player.h"
#include <iostream>
/**
  Construct a new Player object
  **/
Player::Player() :
    location(350, 600),
    health(150),
    lives(5),
    score(0),
    image_flat(QImage(":/ships/res/player_flat.png")),
    image_left(QImage(":/ships/res/player_goingleft.png")),
    image_right(QImage(":/ships/res/player_goingright.png")),
    image(QImage(":/ships/res/player_flat.png")),
    bullet_image(QImage(":/ships/res/bullet_standard_player.png")),
    std_bullet(QImage(":/ships/res/bullet_standard_player.png")),
    bullet_loc(0,0),
    direction(0,0),
    blink_time(0)
{
}

/**
  Fire the Player bullet if the bullet is not already active
  **/
void Player::fire() {
    if (!bulletActive()) bullet_loc = location-QPoint(0, image.height()/2+5);
}

/**
  Get the visual representation of the Player bullet
  @return bullet image
  **/
QImage Player::getBulletImage() {
    return std_bullet;
}

/**
  Get the location of the Player bullet (adjusted for display)
  @return adjusted bullet location
  **/
QPoint Player::getBulletLoc() {
    return bullet_loc - QPoint(bullet_image.width()/2, bullet_image.height()/2);
}

/**
  Get the location of the Player bullet (centerpoint - not adjusted)
  @return non-adjusted bullet location
  **/
QPoint Player::getBulletRawLoc() {
    return bullet_loc;
}

/**
  Instruct the player to blink for @param time
  @param time time to blink in ms
  **/
void Player::blink(int time) {
    blink_time = time;
}

/**
  Jump the player to @param loc
  @param loc the location to jump to
  **/
void Player::setLocation(QPoint loc) {
    location = loc;
}

/**
  Check if the player should be displayed (used for blink effect)
  @return whether the player is currently invisible due to blink
  **/
bool Player::getBlink() {
    if (blink_time>0) {
        blink_time-=10;
        return (blink_time%51>25);
    } else return false;
}

/**
  get the location of the player on the GraphicsScene
  @return the upper left hand corner of the object
  **/
QPoint Player::getLocation() {
    return location-QPoint(image.width()/2, image.height()/2);
}

/**
  get the non-adjusted location (midpoint) of the player on the GraphicsScene
  @return the center of the object
  **/
QPoint Player::getRawLocation() {
    return location;
}

/**
  Get the number of lives remaining
  @return lives
  **/
int Player::getLives() {
    return lives;
}

/**
  Get the health remaining
  @return health
  **/
int Player::getHealth() {
    return health;
}

/**
  Set the player's health
  @param newhealth the new health value
  **/
void Player::setHealth(int newhealth) {
    health = newhealth;
}

/**
  Respond to key input
  @param event          The key event
  @param releaseEvent   Whether the event was fired in keyReleaseEvent() or not
  **/
void Player::keyInput(QKeyEvent *event, bool releaseEvent) {
    switch(event->key()) {
    case Qt::Key_A:
        if(releaseEvent) {
            //std::cout << "Key_Left released" << std::endl;
            if (direction.x()<0) direction.setX(0);
        } else {
            //std::cout << "Key_Left pressed" << std::endl;
            direction.setX(-8);
        }
        break;
    case Qt::Key_D:
        if(releaseEvent) {
            //std::cout << "Key_Right released" << std::endl;
            if (direction.x()>0) direction.setX(0);
        }else {
            //std::cout << "Key_Right pressed" << std::endl;
            direction.setX(8);
        }
        break;
    case Qt::Key_W:
        if(releaseEvent) {
            if (direction.y()<0) direction.setY(0);
        } else {
            direction.setY(-8);
        }
        break;
    case Qt::Key_S:
        if(releaseEvent) {
            if (direction.y()>0) direction.setY(0);
        } else {
            direction.setY(8);
        }
        break;
    case Qt::Key_Space:
        fire();
        break;
    default:
        break;
    }
}

/**
  move the Player according to Player::direction
  **/
void Player::move() {
    location+=direction;
    if (location.x()<0) location.setX(0);
    if (location.x()>700) location.setX(700);
    if (location.y()<0+image.height()/2) location.setY(0+image.height()/2);
    if (location.y()>700-image.height()/2) location.setY(700-image.height()/2);
}

/**
  move the bullet if active
  **/
void Player::moveBullet() {
    if(bulletActive()) bullet_loc+=QPoint(0,-18);
    if (bullet_loc.y() < 5) resetBullet();
}

/**
  get the status of the bullet
  @return whether the bullet is active
  **/
bool Player::bulletActive() {
    return (bullet_loc.x()>0 && bullet_loc.y()>0);
}

/**
  reset the bullet to inactive
  **/
void Player::resetBullet() {
    bullet_loc = QPoint(0,0);
}

/**
  get the player's score
  @return score
  **/
int Player::getScore() {
    return score;
}

/**
  add to the Player's score
  @param points The points to add to the score
  **/
void Player::addToScore(int points) {
    score += points;
}

/**
  call when the Player has lost a life.
  Score will decrease by 1000 and the player will jump to the default location
  **/
void Player::loseLife() {
    lives--;
    score -= 1000;
    setLocation(QPoint(350, 600));
}

/**
  update the player's image based on the player's direction of travel
  **/
QImage Player::updateImage() {
    if (direction.x()<0) {
        image = image_left;
    } else if (direction.x()>0) {
        image = image_right;
    } else {
        image = image_flat;
    }
    return image;
}

/**
  Have the player take a hit
  @param damage - the damage to subtract from health
  **/
void Player::takehit(int damage) {
    health-= damage;
}

/**
  Get the player's visual representation
  @return image
  **/
QImage Player::getImage() {
    return image;
}




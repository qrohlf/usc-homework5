#include "enemy.h"
#include <iostream>
/**
  Construct a new Enemy object
  @param start_location     The starting location for the enemy
  @param health             The amount of health the enemy starts with
  @param points_per_hit     The number of points the player recieves for shooting the Enemy
  @param points_per_kill    The number of points the player recieves for killing the Enemy
  @param new_pixmap         The image used to display the Enemy
  **/
Enemy::Enemy(QPoint start_location, int health, int points_per_hit, int points_per_kill, QImage new_pixmap) :
    location(start_location),
    health(health),
    points_per_hit(points_per_hit),
    points_per_kill(points_per_kill),
    image(new_pixmap),
    dead(false)
{
}

/**
  Get the Enemy's points_per_kill
  @return The points per kill
  **/
int Enemy::killPoints() {
    return points_per_kill;
}

/**
  Get the location of the Enemy
  @return a QPoint with the Enemy location (adjusted for display)
  **/
QPoint Enemy::getLocation()
{
    return location-QPoint(image.width()/2, image.height()/2);
}

/**
  get the non-adjusted location (midpoint) of the enemy on the GraphicsScene
  @return the center of the object
  **/
QPoint Enemy::getRawLocation() {
    return location;
}

/**
  Get the Enemy's health
  @return health
  **/
int Enemy::getHealth() {
    return health;
}

/**
  Signal the enemy to take a hit
  @param damage The damage to deal to the Enemy
  @return score The points to be awarded for hitting and/or killing the Enemy
  **/
int Enemy::takehit(int damage) {
    health -= damage;
    if (health > 0) return points_per_hit;
    else {
        dead = true;
        return points_per_kill;
    }
}

/**
  Set the Enemy's visual representation
  @param new_image The new image to display for the Enemy
  **/
void Enemy::setImage(QImage new_image) {
    image = new_image;
}

/**
  Get the Enemy's visual representation
  @return The QImage used to display the Enemy
  **/
QImage Enemy::getImage() {
    return image;
}

/**
  Destroy the Enemy
  **/
Enemy::~Enemy() {
}

/**
  Kill the Enemy (deprecated, use setHealth(0) instead)
  @deprecated use setHealth(0) instead
  **/
void Enemy::die() {
    dead = true;
}

/**
  Move the Enemy dx pixels left
  @param dx
  **/
void Enemy::moveLeft(int dx) {
    location+=QPoint(-dx, 0);
    if (location.x()<0) location.setX(0);
}

/**
  Move the Enemy dx pixels right
  @param dx
  **/
void Enemy::moveRight(int dx) {
    location+=QPoint(dx, 0);
    if (location.x()>700) location.setX(700);
}

/**
  Move the Enemy dy pixels up
  @param dy
  **/
void Enemy::moveUp(int dy) {
    location+=QPoint(0, -dy);
    if (location.y()<0+image.height()/2) location.setY(0+image.height()/2);
}

/**
  Move the Enemy dy pixels down
  @param dy
  **/
void Enemy::moveDown(int dy) {
    location+=QPoint(0, dy);
    if (location.y()>700-image.height()/2) location.setY(700-image.height()/2);
}

/**
  Check if the dead flag has been set on the Enemy
  @deprecated use getHealth() instead
  @return whether the enemy is dead
  **/
bool Enemy::isDead() {
    return dead;
}

/**
  Shoot method for Enemy abstract base class
  @return NULL
  **/
Enemy* Enemy::shoot(QPoint player_loc) {
    return NULL;
}



#ifndef PLAYER_H
#define PLAYER_H

#include <QPoint>
#include <QPixmap>
#include <QKeyEvent>

/**
  @brief The hero, Player

  This object keeps track of score, health, lives, and every other aspect of the Player
  **/
class Player
{
public:
    Player();
    QPoint getLocation();
    QPoint getRawLocation();
    void keyInput(QKeyEvent *event, bool releaseEvent);
    void move();
    QImage updateImage();
    void takehit(int damage);
    QImage getImage();
    void setHealth(int health);
    int getScore();
    int getLives();
    int getHealth();
    void fire();
    QPoint getBulletLoc();
    QPoint getBulletRawLoc();
    QImage getBulletImage();
    void moveBullet();
    void resetBullet();
    bool bulletActive();
    void addToScore(int points);
    void loseLife();
    void blink(int time);
    bool getBlink();
    void setLocation(QPoint loc);
private:
    ///The player's health remaining
    int health;
    ///The player's lives remaining
    int lives;
    ///The player's score
    int score;
    ///The player's location
    QPoint location;
    ///The player's direction of travel
    QPoint direction;
    ///The current visual representation
    QImage image;
    QImage image_flat;
    QImage image_left;
    QImage image_right;
    ///Location of the player's bullet
    QPoint bullet_loc;
    ///Standard bullet image
    QImage std_bullet;
    ///Bullet image currently in use (allows for later expansion of game via powerups/different guns)
    QImage bullet_image;
    ///Keep track of how much longer the player should blink
    int blink_time;
};

#endif // PLAYER_H

#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsPixmapItem>
#include <QPixmap>

/**
  @brief The abstract base class for all Enemies
  **/
class Enemy
{
    public:
        virtual QPoint getLocation();
        QPoint getRawLocation();
        virtual void move(QPoint player_loc) = 0;
        virtual std::string getType() = 0;
        int takehit(int damage);
        virtual QImage getImage();
        int getHealth();
        ~Enemy();
        bool isDead();
        int killPoints();
        void die();
        virtual Enemy* shoot(QPoint player_loc);
        void setImage(QImage new_image);
    protected:
        Enemy(QPoint start_location, int health, int points_per_hit, int points_per_kill, QImage image);
        ///The health of the Enemy
        int health;
        ///The location of the Enemy
        QPoint location;
        ///The points awarded per hit of the Enemy
        const int points_per_hit;
        ///The points awarded per kill of the Enemy
        const int points_per_kill;
        ///The visual used to draw the Enemy
        QImage image;
        void moveLeft(int dx);
        void moveRight(int dx);
        void moveUp(int dy);
        void moveDown(int dy);
        ///death flag @deprecated death is now determined by health
        bool dead;
};

#endif // ENEMY_H

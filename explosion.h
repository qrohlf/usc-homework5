#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "enemy.h"

/**
  @brief A special type of Enemy used to animate the explosion of other Enemies
  Explosions are exempt from collision and bullet-hit checking
  **/
class Explosion : public Enemy
{
public:
    Explosion(QPoint starting_location, int duration);
    void move(QPoint player_loc);
    std::string getType();
    QImage getImage();
    QPoint getLocation();
    void setScale(int width, int height);
private:
    ///The number of ms left in the Explosion's lifetime
    int ms_left;
    const QImage explosion_1;
    const QImage explosion_2;
    const QImage explosion_3;
    const QImage explosion_4;
    ///The width to scale the Explosion to
    int w_scale;
    ///The height to scale the Explosion to
    int h_scale;
};

#endif // EXPLOSION_H

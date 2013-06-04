#include "giantboss.h"
#include "kamikaze.h"
#include "detonator.h"
#include "bullet.h"
/**
  Really massive boss for the final level.
  @param start_location The Boss's starting location.
  **/
GiantBoss::GiantBoss(QPoint start_location) :
    Enemy(start_location, 750, 5, 1000, QImage(":/ships/res/giantboss.png")),
    counter(1)
{
}

/**
  Move the GiantBoss side to side and increment the looping counter
  @param player_loc unused
  **/
void GiantBoss::move(QPoint player_loc) {
    counter = (counter+1)%1400;
    if (counter > 700) moveLeft(1);
    if (counter < 700) moveRight(1);
}

std::string GiantBoss::getType() {
    return "GiantBoss";
}

/**
  Give the GiantBoss an opportunity to shoot.
  @param player_loc the Player's location
  @return an Enemy* of some kind. The GiantBoss shoots a lot of different things.
  **/
Enemy* GiantBoss::shoot(QPoint player_loc) {
    static int kamikaze, detonator, lazers, bigbullet, missiles;
    if (counter%300 == 0) {
        kamikaze = rand()%300;
        detonator = rand()%300;
        lazers = rand()%200;
        bigbullet = rand()%200;
        missiles = rand()%200;
    }
    int tempcounter = counter %300;
    if (tempcounter == kamikaze || tempcounter == kamikaze+30 || tempcounter == kamikaze+60) {
        return new Kamikaze(location, -100, false);
    } else if(tempcounter == detonator) {
        return new Detonator(location+QPoint(-30, 0), -100);
    }else if(tempcounter == detonator+1) {
        return new Detonator(location+QPoint(30, 0), -100);
    }else if (tempcounter > lazers && tempcounter < lazers+100) {
        Bullet* b = new Bullet(location+QPoint((tempcounter%2)?-30:30, 0), 1, QPoint(0, 10));
        b->setImage(QImage(":/ships/res/lazer.png"));
        return b;
    } else if (tempcounter == bigbullet || tempcounter+30 == bigbullet) {
        QPoint direction = location-player_loc;
        direction.setX((direction.x()>0)?-6:6);
        direction.setY(6);
        Bullet* b = new Bullet(location, 30, direction);
        b->setImage(QImage(":/ships/res/bigbullet.png"));
        return b;
    } else if (tempcounter == missiles || tempcounter == missiles+1 || tempcounter == missiles+2 || tempcounter == missiles+3) {
        QPoint direction = location-player_loc;
        direction.setX(4*direction.x()/direction.y());
        direction.setY(4);
        Bullet* b = new Bullet(location+QPoint((tempcounter%2)?50:-50, 0), 20, direction);
        b->setImage(QImage(":/ships/res/missile.png"));
        b->setHoming(true);
        return b;
    }   else return NULL;

}

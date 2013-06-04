#ifndef SWOOPFIGHTER_H
#define SWOOPFIGHTER_H
#include "fighter.h"

/**
  @brief A Fighter which will swoop down at the player, then rejoin the herd

  (ticks_until_charge should always be a multiple of 200)
  **/
class Swoopfighter : public Fighter
{
public:
    Swoopfighter(QPoint start_location, int ticks_until_charge = 200);
    virtual void move(QPoint player_loc);
    virtual Enemy* shoot(QPoint player_loc);
protected:
    ///Ticks before the Swoopfighter should swoop
    int ticks_until_charge;
    ///Ticks between swoops
    int ticks_until_charge_original;
    ///Keep track of the elapsed ticks
    int ticks;
    ///Keep track of where the Swoopfighter should return to
    QPoint start_location;
    ///Whether the Swoopfighter is currently swooping
    bool swoop;
};

#endif // SWOOPFIGHTER_H

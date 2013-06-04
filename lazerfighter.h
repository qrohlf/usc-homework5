#ifndef LAZERFIGHTER_H
#define LAZERFIGHTER_H
#include "fighter.h"

/**
  @brief Fighter Enemy which fires a steady stream of lazer bullets every second or two
  **/
class LazerFighter : public Fighter
{
public:
    LazerFighter(QPoint start_location);
    virtual Enemy* shoot(QPoint player_loc);
protected:
    ///Keep track of the elapsed ticks to determine shooting time
    int ticks;
};

#endif // LAZERFIGHTER_H

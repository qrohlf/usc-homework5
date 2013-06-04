#ifndef ENEMYLISTITEM_H
#define ENEMYLISTITEM_H
#include "enemy.h"
#include <QGraphicsPixmapItem>
class EnemyListItem
{
public:
    EnemyListItem();
    QGraphicsPixmapItem *graphic;
    Enemy *enemy;
    ~EnemyListItem();
};

#endif // ENEMYLISTITEM_H

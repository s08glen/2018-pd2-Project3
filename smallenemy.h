#ifndef SMALLENEMY_H
#define SMALLENEMY_H
#include "enemybase.h"
#include <QString>

class smallenemy : public enemybase
{
public:
    smallenemy();

public slots:
    void show();
    void move();
    void attack();
};

#endif // SMALLENEMY_H

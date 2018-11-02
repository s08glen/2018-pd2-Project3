#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QDebug>

class enemybase : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemybase();
    int hp,a,b;

public slots:
    virtual void show()=0;
    virtual void move()=0;
    virtual void attack()=0;

private:
    //int hp;
};

#endif // ENEMYBASE_H

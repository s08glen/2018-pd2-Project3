#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class bullet : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    bool bullethituser;
    int velo;

public slots:
    void fly();
    void enemybulletfly();
};

#endif // BULLET_H

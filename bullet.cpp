#include "bullet.h"

bullet::bullet()
{
    bullethituser = false;
    /*QPixmap play(":/res/bullet.png");
    this->setPixmap(play.scaled(10,10));
    this->setPos(200,500);*/
    velo = 3;
}
void bullet::fly()
{
    setPos(x(), y() - 3);
    if(y() < -100) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::enemybulletfly(){
    setPos(x(), y() + velo);
    if(y() > 850) {
        this->scene()->removeItem(this);
        delete this;
    }
}

#include "smallenemy.h"

smallenemy::smallenemy()
{
    a=-1;
    b=-1;
}

void smallenemy::show(){
    //QString str = ":/res/windows.png";
    //setPixmap(QPixmap(str).scaled(50, 50));
    hp=1000;
    //qDebug()<<hp;
}

void smallenemy::move(){
    setPos(x()+a, y()+b);
    if((x()+a) <= 0 || (x()+a)>=600) {
        a=-a;
    }
    if((y()+b) <= 30 || (y()+b)>=400) {
        b=-b;
    }
}

void smallenemy::attack(){

}

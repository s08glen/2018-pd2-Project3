#include "maincharacter.h"

maincharacter::maincharacter()
{
    QPixmap google(":/res/google.png");
    this->setPixmap(google.scaled(30,30));
    this->setPos(290,700);
    hp=1000;
}

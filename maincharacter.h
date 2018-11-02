#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include <QObject>
#include <QGraphicsPixmapItem>

class maincharacter : public QObject ,public QGraphicsPixmapItem
{
public:
    maincharacter();
    int hp;
};

#endif // MAINCHARACTER_H

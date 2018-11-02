#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QString>
#include "maincharacter.h"
#include "bullet.h"
#include <QKeyEvent>
#include "smallenemy.h"
#include <QString>
#include <vector>
#include <QObject>
#include <QProgressBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *base;
    QTimer *fps,*shoottime;
    maincharacter *google;
    bullet *play,*enemybullet;
    smallenemy *small1,*small2,*small3;
    bool up,down,left,right,shoot,end,hpall,skillbool;
    std::vector<bullet*> bvec;
    std::vector<bullet*> ebvec;
    std::vector<enemybase*> evec;
    std::vector<QProgressBar*> ehpbar;
    int point,hp,dead,amount;
    QProgressBar *hpbar[3];

public slots:
    void refresh();
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

};

#endif // MAINWINDOW_H

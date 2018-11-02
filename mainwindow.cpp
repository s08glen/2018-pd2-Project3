#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincharacter.h"
#include <cmath>
#include "bullet.h"
#include <QDebug>
#include "enemybase.h"
#include "smallenemy.h"
#include <vector>
#include <cmath>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    up=false;down=false;left=false;right=false;shoot=false;point=0;end=false;dead=0;amount=0;skillbool=false;
    ui->setupUi(this);
    base = new QGraphicsScene(0,0,600,800);
    ui->graphicsView->setScene(base);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    //ui->graphicsView->setStyleSheet("background-image:'/res/google.png'");
    ui->text->setText("4");
    ui->point->hide();
    ui->small1hp->setValue(100);//ui->enemyhp1->setValue(100);
    //ui->enemyhp2->setValue(100);ui->enemyhp3->setValue(100);
    //ui->p->hide();
    fps = new QTimer;
    shoottime = new QTimer;
    fps->start(8);
    google = new maincharacter;
    play = new bullet;
    base->addItem(google);
    base->addItem(play);
    this->setFocusPolicy(Qt::NoFocus);
    hp=10;
    ui->googlehp->display(hp);
    if(!end){
        connect(fps,SIGNAL(timeout()),this,SLOT(refresh()));
        connect(fps,SIGNAL(timeout()),base,SLOT(update()));
    }
}

void MainWindow::refresh(){
    int enemyhp=0;
    static int count =0,time=0,skill=0,skillcount=0,skilltime=0;
    //int hptemp=0;
    time++;
    count++;
    skill++;
    //qDebug()<<time<<endl;
    if (count>=101){
        count = 0;
    }
    else if (count%10==0){
        if(shoot){
            play = new bullet;            
            play->setPixmap(QPixmap(":/res/bullet.png").scaled(15,15));
            play->setPos(google->x() + google->pixmap().width() / 2 - play->pixmap().width() / 2, google->y() - play->pixmap().height());
            play->connect(fps, SIGNAL(timeout()), play, SLOT(fly()));
            base->addItem(static_cast<QGraphicsPixmapItem*>(play));
            bvec.push_back(play);
            //qDebug()<<play->x()<<play->y()<<endl;
        }
    }
    int x=google->x()+15,y=google->y()+15;
    this->setFocus();
    if(x>=600){
        right=false;
    }
    if(x<=0){
        left=false;
    }
    if(y>=800){
        down=false;
    }
    if(y<=0){
        up=false;
    }
    if(up&&left){
            google->setPos(google->x()-3/sqrt(2),google->y()-3/sqrt(2));
    }
    else if(up&&right){
            google->setPos(google->x()+3/sqrt(2),google->y()-3/sqrt(2));
    }
    else if(down&&left){
            google->setPos(google->x()-3/sqrt(2),google->y()+3/sqrt(2));
    }
    else if(down&&right){
            google->setPos(google->x()+3/sqrt(2),google->y()+3/sqrt(2));
    }
    else if(up){
       google->setPos(google->x(),google->y()-3);
    }
    else if(down){
        google->setPos(google->x(),google->y()+3);
    }
    else if(left){
        google->setPos(google->x()-3,google->y());
    }
    else if(right){
        google->setPos(google->x()+3,google->y());
    }
    else{
        google->setPos(google->x(),google->y());
    }
    switch(time){
    case 100:
        small1 = new smallenemy;
        small1->show();
        small1->setPos(290,200);
        small1->setPixmap(QPixmap(":/res/windows.png").scaled(50, 50));
        //small1->a = 0; small1->b=0;
        base->addItem(static_cast<QGraphicsPixmapItem*>(small1));
        evec.push_back(small1);
        //ui->small1hp->show();
        //ui->small1hp->setGeometry(small1->x()+120,(small1->y()-30),100,10);
        hpbar[amount] = new QProgressBar(ui->centralWidget);
        hpbar[amount]->setGeometry(880,250,120,30);
        hpbar[amount]->setValue(100);
        hpbar[amount]->show();
        ehpbar.push_back(hpbar[amount]);
        amount++;
        ui->text->setText("3");
        break;

    case 200:
        small2 = new smallenemy;
        small2->show();
        small2->setPos(67,146);
        small2->setPixmap(QPixmap(":/res/windows2.png").scaled(50, 50));
        small2->a = 3; small2->b=1;
        base->addItem(static_cast<QGraphicsPixmapItem*>(small2));
        evec.push_back(small2);
        ui->text->setText("2");
        hpbar[amount] = new QProgressBar(ui->centralWidget);
        hpbar[amount]->setGeometry(880,300,120,30);
        hpbar[amount]->setValue(100);
        hpbar[amount]->show();
        ehpbar.push_back(hpbar[amount]);
        amount++;
        break;

    case 300:
        small3 = new smallenemy;
        small3->show();
        small3->setPixmap(QPixmap(":/res/windows3.png").scaled(50, 50));
        small3->setPos(167,100);
        small3->a = 5;
        base->addItem(static_cast<QGraphicsPixmapItem*>(small3));
        evec.push_back(small3);
        hpbar[amount] = new QProgressBar(ui->centralWidget);
        hpbar[amount]->setGeometry(880,350,120,30);
        hpbar[amount]->setValue(100);
        hpbar[amount]->show();
        ehpbar.push_back(hpbar[amount]);
        amount++;
        ui->text->setText("1");
        break;

    case 400:
        ui->text->setText("Go");
        break;
    case 500:
        ui->text->hide();
        break;
    }
    if(count%50==0 && count!=0 && time>=600){
        for(vector<enemybase*>::iterator k=evec.begin();k != evec.end();){
            enemybullet = new bullet;
            enemybullet->setPixmap(QPixmap(":/res/enemybullet.png").scaled(15,15));
            enemybullet->setPos((*k)->x() + (*k)->pixmap().width() / 2 - enemybullet->pixmap().width() / 2, (*k)->y() + enemybullet->pixmap().height());
            enemybullet->connect(fps, SIGNAL(timeout()), enemybullet, SLOT(enemybulletfly()));
            base->addItem(static_cast<QGraphicsPixmapItem*>(enemybullet));
            ebvec.push_back(enemybullet);
            k++;
        }
    }
for(unsigned int j=0;j<evec.size();j++){
    for(unsigned int i=0;i<ebvec.size();i++){
        if((ebvec.at(i)->x()-google->x()) <=30 && (ebvec.at(i)->x()-google->x()) >=-10 ){
            if((ebvec.at(i)->y()-google->y()) <=30 && (ebvec.at(i)->y()-google->y()) >=-10 ){
                ebvec.at(i)->setOpacity(0);
                //qDebug()<<"attack"<<i<<j;
                if(!(ebvec.at(i)->bullethituser)){
                    hp--;
                    google->hp--;
                    ebvec.at(i)->bullethituser=true;
                }
                ebvec.at(i)->bullethituser=true;
            }
        }
        //else qDebug()<<"no";
        ui->googlehp->display(hp);
        //ebvec.at(i)->bullethituser=false;
        //qDebug()<<google->hp<<hp;
        if(hp<=0){
            end=true;            
            //qDebug()<<end;
            fps->stop();
            ui->text->show();
            ui->point->show();
            ui->text->setStyleSheet("color:red;");
            ui->text->setText("You LOSE!!!!!");
            ui->point->display(point);
            //qDebug()<<point;
        }
        if(ebvec.at(i)->y() >= 800){
            ebvec.erase(ebvec.begin());
        }
    }
    enemyhp = enemyhp+evec.at(j)->hp;
    //qDebug()<<enemyhp;
    if(skillbool){
        if(skillcount<=2){
            ebvec.at(j)->velo=1;
            if(skilltime==0){
                skilltime = time;
                skillcount++;
            }

            if((time-skilltime)>300){
                skillbool=false;
                skilltime=0;
                hp+=2;
                ebvec.at(j)->velo=3;
            }
        }
        else{
            skillbool=false;
        }
    }
    //qDebug()<<skillbool<<skillcount;
}
    //enemyhp =
    ui->small1hp->setValue(enemyhp/30);

    for(unsigned int i=0;i<bvec.size();i++){
        for(unsigned int j=0;j<evec.size();j++){
            if((bvec.at(i)->x()-evec.at(j)->x()) <= 50 && (bvec.at(i)->x()-evec.at(j)->x()) >=0){
                if (abs(bvec.at(i)->y()-evec.at(j)->y())<=50){
                        bvec.at(i)->setOpacity(0);
                        evec.at(j)->hp--;
                        ehpbar.at(j)->setValue((evec.at(j)->hp)/10);
                    }
                }
            //qDebug()<<j<<evec.at(j)->hp;
            if(evec.at(j)->hp < 0){
                //qDebug()<<evec.at(j)->hp;
                evec.at(j)->setOpacity(0);
                ehpbar.at(j)->hide();
                bvec.at(i)->setOpacity(100);
            }
            for(vector<QProgressBar*>::iterator j=ehpbar.begin();j != ehpbar.end();){
                for(vector<enemybase*>::iterator k=evec.begin();k != evec.end();){
                    if((*k)->hp <=0){
                        //qDebug()<<(*k)->hp;
                        delete (*k);
                        k = evec.erase(k);
                        delete (*j);
                        j = ehpbar.erase(j);
                        point+=(100/3);
                        dead++;
                    }
                    else{
                        k++;
                        j++;
                    }
                }
            }
        }        
    }
    if(time>=400){
        if(dead==amount){
            fps->stop();
            ui->text->show();
            ui->text->setStyleSheet("color:red;");
            ui->text->setText("You Win!!!!!");
            ui->point->show();
            if(time<=10000){
                point = point+(10000-time)/10;
            }
            ui->point->display(point);
            //qDebug()<<dead;
        }
    }
    for(unsigned int i=0;i<bvec.size();i++){
        if(bvec.at(i)->y() <= -50){
            bvec.erase(bvec.begin());
        }
    }
    for(unsigned int j=0;j<evec.size();j++){
        if(time==400){
            evec.at(j)->connect(fps, SIGNAL(timeout()), evec.at(j), SLOT(move()));
        }
        if(time==400){
            evec.at(j)->connect(fps, SIGNAL(timeout()), evec.at(j), SLOT(attack()));            
        }
    }
    //qDebug()<<time;
    if(time<=500){
        shoot=false;//up=false;down=false;left=false;right=false;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!event->isAutoRepeat()){
        if(event->key()==Qt::Key_W || event->key()==Qt::Key_Up){
           up=true;
           down=false;
        }
        else if(event->key()==Qt::Key_S || event->key()==Qt::Key_Down){
            down=true;
            up=false;
        }
        else if(event->key()==Qt::Key_A || event->key()==Qt::Key_Left){
            left=true;
            right=false;
        }
        else if(event->key()==Qt::Key_D || event->key()==Qt::Key_Right){
            right=true;
            left=false;
        }

        else if(event->key()==Qt::Key_Space || event->key()==Qt::Key_Question){
            shoot=true;
        }
        else if(event->key()==Qt::Key_X){
            skillbool=true;
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if(!event->isAutoRepeat()){
        if(event->key()==Qt::Key_W || event->key()==Qt::Key_Up){
           up=false;
        }
        else if(event->key()==Qt::Key_S || event->key()==Qt::Key_Down){
            down=false;
        }
        else if(event->key()==Qt::Key_A || event->key()==Qt::Key_Left){
            left=false;
        }
        else if(event->key()==Qt::Key_D || event->key()==Qt::Key_Right){
            right=false;
        }
        else if(event->key()==Qt::Key_Space || event->key()==Qt::Key_Question){
            shoot=false;
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

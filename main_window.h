#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QBasicTimer>
#include <QPainter>
#include <cmath>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <paintWidget.h>


class MainWin : public QMainWindow
{
   Q_OBJECT

public:
   MainWin(QWidget *parent = nullptr);

   void SetupSpaceship();
   void SetupScene();
   void movePlanet();
   void SetupComet(int&);

   void timerEvent(QTimerEvent* event);
   void paintEvent(QPaintEvent*) ;

private:
   PaintWidget widget_;

   QGraphicsScene* scene_;
   QGraphicsView* view_;

   QPixmap spaceship_;
   QPixmap bkgnd_;
   QPixmap planet_;

   QMovie* movie_;

   QMediaPlayer * m_player;
   QMediaPlaylist * m_playlist;

   QGraphicsPixmapItem* spaceship_item;
   QGraphicsPixmapItem* bkgnd_item;
   QGraphicsPixmapItem* planet_item;

   QBasicTimer animation_timer_;
   QLabel* label_;
   int current_rotate_ = 0;
};
#endif // MAIN_WINDOW_H

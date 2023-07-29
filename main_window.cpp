#include "main_window.h"

MainWin::MainWin(QWidget *parent)
   : QMainWindow(parent)
   ,widget_(new PaintWidget(this))
   , scene_(new QGraphicsScene(this))
   , view_(new QGraphicsView(this))
   , spaceship_(":/spaceship.png")
   , bkgnd_(":/bkgnd.jpg")
   , planet_(":/planet.png")
   , movie_(new QMovie(":/comet.gif"))
   , m_player(new QMediaPlayer(this))
   , m_playlist(new QMediaPlaylist(m_player))
   , bkgnd_item(new QGraphicsPixmapItem())
   , label_(new QLabel(this))
{
   view_->setScene(scene_);
   scene_->addItem(bkgnd_item);
   setFixedSize(1120, 700);

   view_->translate(560, 350);

   animation_timer_.start(50, this);

   m_player->setPlaylist(m_playlist);
   m_playlist->addMedia(QUrl("qrc:/space_sounds.wav"));
   m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
   m_player->play();
}

void MainWin::SetupScene() {
   bkgnd_ = bkgnd_.scaled(1120, 700, Qt::IgnoreAspectRatio);
   scene_->addPixmap(bkgnd_);
   view_->setScene(scene_);
   view_->resize(1120, 700);
   view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWin::SetupSpaceship() {
   spaceship_ = spaceship_.scaled(170, 170 ,Qt::KeepAspectRatio);

   QPixmap rotate(bkgnd_.size());
   rotate = rotate.scaled(700, 700, Qt::IgnoreAspectRatio);
   rotate.fill(QColor(0,0,0,0));

   QPainter paint(&rotate);

   paint.translate(rotate.size().width() / 2, rotate.size().height() / 2);
   paint.rotate(current_rotate_);
   paint.translate(-rotate.size().width() / 2, -rotate.size().height() / 2);
   paint.drawPixmap(-15, 250, spaceship_);

   spaceship_item = scene_->addPixmap(rotate);
   spaceship_item->setPos(210, 0);
}

void MainWin::movePlanet() {
   planet_ = planet_.scaled(1120, 1120 ,Qt::KeepAspectRatio);

   QPixmap rotate(bkgnd_.size());
   rotate = rotate.scaled(500, 500, Qt::IgnoreAspectRatio);
   rotate.fill(QColor(0,0,0,0));

   QPainter paint(&rotate);

   paint.translate(rotate.size().width() / 2, rotate.size().height() / 2);
   paint.rotate(-current_rotate_);
   paint.translate(-rotate.size().width() / 2, -rotate.size().height() / 2);
   paint.drawPixmap(-310, -100,  planet_);

   planet_item = scene_->addPixmap(rotate);
   planet_item->setPos(310, 100);
}

void MainWin::SetupComet(int& rotate) {
   if ((rotate > 60 && rotate < 105) || (rotate > 180 && rotate < 260)) {
      if (!movie_->isValid()) { }

      QSize size = QSize(400, 1120);
      movie_->setScaledSize(size);
      movie_->speed();
      label_->setMovie(movie_);
      label_->setGeometry(-50, -100, 1120, 700);
      label_->show();
      movie_->start();
   } else {
      movie_->stop();
      label_->clear();
   }
}

void MainWin::timerEvent(QTimerEvent* event) {
   if (event->timerId() == animation_timer_.timerId()) {
       widget_.Tick();

       current_rotate_ = widget_.getRotate();
       repaint();
   }
}

void MainWin::paintEvent(QPaintEvent*) {
   scene_->clear();
   SetupScene();
   SetupSpaceship();
   movePlanet();
   SetupComet(current_rotate_);
}

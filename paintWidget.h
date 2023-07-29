#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>

class PaintWidget : public QWidget {
   Q_OBJECT
public:
   explicit PaintWidget(QWidget* parent);
   void Tick();
   int getRotate();

private:
   int current_rotate_ = 0;
};

#endif // PAINTWIDGET_H

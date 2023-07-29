#include "paintWidget.h"

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent) {}

void PaintWidget::Tick() {
  current_rotate_ = (current_rotate_ + 1) % 360;
}

int PaintWidget::getRotate() {
   return current_rotate_;
}

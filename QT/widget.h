#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "triangle.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

        public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     // Объявляем графическую сцену
    Triangle        *triangle;
    QTimer          *timer;// и треугольник
    QGraphicsPixmapItem *pic;
};

#endif // WIDGET\_H

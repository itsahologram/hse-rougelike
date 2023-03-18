#include "triangle.h"

Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0;
    setRotation(angle);
}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-25,-40,50,80);   // Ограничиваем область, в которой лежит треугольник
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon1, pol2;   // Используем класс полигона, чтобы отрисовать треугольник
    // Помещаем координаты точек в полигональную модель
    polygon1 << QPoint(0, -20) << QPoint(-20, 0) << QPoint(20, 0);
    painter->setBrush(Qt::red);     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon1);

    pol2 << QPoint(0, 20) << QPoint(-20, 0) << QPoint(20, 0);
    painter->setBrush(Qt::blue);     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(pol2);

    // Рисуем треугольник по полигональной модели
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Triangle::slotGameTimer()
{
    if (GetAsyncKeyState('A')){
        angle -=5;
        setRotation(angle);
    }

    if (GetAsyncKeyState('D')){
        angle +=5;
        setRotation(angle);
    }

    if (GetAsyncKeyState('W')){
        setPos(mapToParent(0, -5));
    }

    if (GetAsyncKeyState('S')){
        setPos(mapToParent(0, 5));
    }
    if(this->x() - 10 < -250){
        this->setX(-240);       // слева
    }
    if(this->x() + 10 > 250){
        this->setX(240);        // справа
    }

    if(this->y() - 10 < -250){
        this->setY(-240);       // сверху
    }
    if(this->y() + 10 > 250){
        this->setY(240);        // снизу
    }
}

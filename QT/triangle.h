#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <windows.h>

// Наследуемся от QGraphicsItem
class Triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT;
public:
    explicit Triangle(QObject *parent = nullptr);
    ~Triangle();

signals:
public slots:
    void slotGameTimer();
protected:
    QRectF boundingRect() const;    /* Определяем виртуальный метод,
                                     * который возвращает область, в которой
                                     * находится треугольник
                                     * */
    /* Определяем метод для отрисовки треугольника
     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    qreal angle;
};
#endif // TRIANGLE_H

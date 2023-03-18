#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(600,600);          // Задаем размеры виджета, то есть окна
    this->setFixedSize(600,600);    // Фиксируем размеры виджета

    scene = new QGraphicsScene();   // Инициализируем графическую сцену
    triangle = new Triangle();      // Инициализируем треугольник
    pic = new QGraphicsPixmapItem();


    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Откл

    scene->setSceneRect(-250,-250,500,500); // Устанавливаем область графической сцены

    scene->addLine(-250,0,250,0,QPen(Qt::black));   // Добавляем горизонтальную линию через центр
    scene->addLine(0,-250,0,250,QPen(Qt::black));   // Добавляем вертикальную линию через центр

    scene->addLine(-250,-250, 250,-250, QPen(Qt::black));
    scene->addLine(-250, 250, 250, 250, QPen(Qt::black));
    scene->addLine(-250,-250,-250, 250, QPen(Qt::black));
    scene->addLine( 250,-250, 250, 250, QPen(Qt::black));

    scene->addItem(triangle);
    triangle->setPos(0,0);      // Устанавливаем треугольник в центр сцены

    timer = new QTimer();
    connect(timer, &QTimer::timeout, triangle, &Triangle::slotGameTimer);
    timer->start(1000/50);


}

Widget::~Widget()
{
    delete ui;
}

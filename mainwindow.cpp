#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>

void animate_item(MyGraphicsEllipseItem * item) {
    int duration = 3000;
    const int multiplier = 3;

    QPointF pos = item->scenePos();
    int size = item->rect().width() * multiplier;

    QPointF left_top(pos);
    QPointF right_top(pos.x() + size, pos.y());
    QPointF right_bottom(pos.x() + size, pos.y() + size);
    QPointF left_bottom(pos.x(), pos.y() + size);


    // Добавим траекторию
    QGraphicsRectItem * traj = new QGraphicsRectItem();
    traj->setPen(QPen(Qt::DashLine));
    traj->setRect(item->rect().x() + item->rect().width() / 2, item->rect().y() + item->rect().width() / 2,
                  item->rect().width() * multiplier,
                  item->rect().height() * multiplier);
    QGraphicsScene * scene = item->scene();
    scene->addItem(traj);


    QPropertyAnimation * anim1 = new QPropertyAnimation(item, "pos");
    anim1->setDuration(duration);
    anim1->setStartValue(left_top);
    anim1->setEndValue(right_top);

    QPropertyAnimation * anim2 = new QPropertyAnimation(item, "pos");
    anim2->setDuration(duration);
    anim2->setStartValue(right_top);
    anim2->setEndValue(right_bottom);

    QPropertyAnimation * anim3 = new QPropertyAnimation(item, "pos");
    anim3->setDuration(duration);
    anim3->setStartValue(right_bottom);
    anim3->setEndValue(left_bottom);

    QPropertyAnimation * anim4 = new QPropertyAnimation(item, "pos");
    anim4->setDuration(duration);
    anim4->setStartValue(left_bottom);
    anim4->setEndValue(left_top);

    QSequentialAnimationGroup * group = new QSequentialAnimationGroup();
    group->setLoopCount(-1);
    group->addAnimation(anim1);
    group->addAnimation(anim2);
    group->addAnimation(anim3);
    group->addAnimation(anim4);
    group->start();
}

void animate_item(MyGraphicsRectItem * item) {
    int duration = 3000;
    const int multiplier = 3;

    QPointF pos = item->scenePos();
    int size = item->rect().width() * multiplier;

    QPointF left_top(pos);
    QPointF right_top(pos.x() + size, pos.y());
    QPointF right_bottom(pos.x() + size, pos.y() + size);
    QPointF left_bottom(pos.x(), pos.y() + size);


    // Добавим траекторию
    QGraphicsEllipseItem * traj = new QGraphicsEllipseItem();
    traj->setPen(QPen(Qt::DashLine));
    traj->setRect(item->rect().x(), item->rect().y(),
                  item->rect().width() * multiplier,
                  item->rect().height() * multiplier);
    QGraphicsScene * scene = item->scene();
    scene->addItem(traj);


    QPropertyAnimation * anim1 = new QPropertyAnimation(item, "pos");
    anim1->setDuration(duration);
    anim1->setStartValue(left_top);
    anim1->setEndValue(right_top);

    QPropertyAnimation * anim2 = new QPropertyAnimation(item, "pos");
    anim2->setDuration(duration);
    anim2->setStartValue(right_top);
    anim2->setEndValue(right_bottom);

    QPropertyAnimation * anim3 = new QPropertyAnimation(item, "pos");
    anim3->setDuration(duration);
    anim3->setStartValue(right_bottom);
    anim3->setEndValue(left_bottom);

    QPropertyAnimation * anim4 = new QPropertyAnimation(item, "pos");
    anim4->setDuration(duration);
    anim4->setStartValue(left_bottom);
    anim4->setEndValue(left_top);

    QSequentialAnimationGroup * group = new QSequentialAnimationGroup();
    group->setLoopCount(-1);
    group->addAnimation(anim1);
    group->addAnimation(anim2);
    group->addAnimation(anim3);
    group->addAnimation(anim4);
    group->start();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // Установим сглаживание

    // Размер окна и сцены
    resize(500, 500);
    scene.setSceneRect(QRectF(QPointF(0, 0), size()));
    ui->graphicsView->resize(size());

    // Инициализация генератора псевдослучайных чисел
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    /// Добаввление квадратов и кругов на сцену ///
    int m = 5; // квадраты
    int n = 3; // кругов

//    for (int i = 0; i < m; i++) {
//        MyGraphicsRectItem * rectItem = new MyGraphicsRectItem(); // создание класс Квадрат
//        // случайный цвет в rgb
//        rectItem->setBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
//        int x = qrand() % (ui->graphicsView->width() - 100);
//        int y = qrand() % (ui->graphicsView->height() - 100);
//        int s = (qrand() % 50) + 20;
//        rectItem->setRect(x, y, s, s); // установка положения и размера
//        scene.addItem(rectItem); // добавление на сцену
//        rect_items.append(rectItem); // добавление в список

//        animate_item(rectItem); // Анимируем объект
//    }


    for (int i = 0; i < n; i++) {
        MyGraphicsEllipseItem * ellipseItem = new MyGraphicsEllipseItem(); // создание класс Круг
        // случайный цвет в rgb
        ellipseItem->setBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
        int x = qrand() % (ui->graphicsView->width() / 2);
        int y = qrand() % (ui->graphicsView->height() / 2);
        int s = (qrand() % 50) + 20;
        ellipseItem->setRect(x, y, s, s); // установка положения и размера
        scene.addItem(ellipseItem); // добавление на сцену
        ellipse_items.append(ellipseItem); // добавление в список

        animate_item(ellipseItem); // Анимируем объект
    }


//    MyGraphicsEllipseItem * ellipseItem = ellipse_items[0];
//    animate_item(ellipseItem);


    QObject::connect(&timer, SIGNAL(timeout()), SLOT(slot_updateScene()));
    timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_updateScene()
{

}

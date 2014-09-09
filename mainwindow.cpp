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
    const int multiplier = 10;

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

    QSequentialAnimationGroup * group = new QSequentialAnimationGroup(item);
    group->setLoopCount(-1);
    group->addAnimation(anim1);
    group->addAnimation(anim2);
    group->addAnimation(anim3);
    group->addAnimation(anim4);
    group->start();
}

#include <math.h>
void animate_item(MyGraphicsRectItem * item) {
    const int multiplier = 10;

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


    QSequentialAnimationGroup * group = new QSequentialAnimationGroup(item);
    group->setLoopCount(-1);

    float DEG2RAD = (float)(3.14159 / 180);
    QPointF lastPos(0, 0);
    for (int i = 0; i < 360; i++)
    {
        float radius = size / 2;
        float degInRad = i * DEG2RAD;
        float x = cos(degInRad) * radius + traj->pos().x() + radius / 2;
        float y = sin(degInRad) * radius + traj->pos().y() + radius / 2;

        QPropertyAnimation * anim = new QPropertyAnimation(item, "pos");
        anim->setDuration(10);
        anim->setStartValue(lastPos);
        anim->setEndValue(QPointF(x, y));

        lastPos = QPointF(x, y);
        group->addAnimation(anim);
    }

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
    resize(800, 800);
    scene.setSceneRect(QRectF(QPointF(0, 0), size()));
    ui->graphicsView->resize(size());

    // Инициализация генератора псевдослучайных чисел
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    /// Добаввление квадратов и кругов на сцену ///
    int m = 5; // квадраты
    int n = 3; // кругов

    for (int i = 0; i < m; i++) {
        MyGraphicsRectItem * rectItem = new MyGraphicsRectItem(); // создание класс Квадрат
        rectItem->setData(Qt::UserRole + 1, 111); // для идентификации элемента
        // случайный цвет в rgb
        rectItem->setBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
        int x = (qrand() % (ui->graphicsView->width() - 200)) + 100;
        int y = (qrand() % (ui->graphicsView->height() - 200)) + 100;
        int s = (qrand() % 50) + 20;
        rectItem->setRect(x, y, s, s); // установка положения и размера
        scene.addItem(rectItem); // добавление на сцену
        rect_items.append(rectItem); // добавление в список

        animate_item(rectItem); // Анимируем объект
    }

    for (int i = 0; i < n; i++) {
        MyGraphicsEllipseItem * ellipseItem = new MyGraphicsEllipseItem(); // создание класс Круг
        ellipseItem->setData(Qt::UserRole + 1, 777); // для идентификации элемента
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


    QTimer * timer = new QTimer(this);
    timer->setInterval(33); // таймер активируется каждые 33 миллисекунды = 0.033 секунды
    QObject::connect(timer, SIGNAL(timeout()), SLOT(slots_checking_for_collision()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slots_checking_for_collision()
{
//    foreach (MyGraphicsEllipseItem * item, ellipse_items) {
//        // Получим список элементов, с которым данный столкнулся:
//        QList <QGraphicsItem *> colliding =  item->collidingItems();
//        if (colliding.isEmpty())
//            continue;

//        item->collidesWithItem()
//    }

//    foreach (MyGraphicsRectItem * item, rect_items) {

//    }

    // Все элементы () на сцене
    foreach (QGraphicsItem * item, scene.items()) {
        int data = item->data(Qt::UserRole + 1).toInt();
        if (data == 777 || data == 111) {
            // Получим список элементов, с которым данный столкнулся:
            QList <QGraphicsItem *> colliding =  item->collidingItems();
            foreach (QGraphicsItem * other, colliding) {
                int item_size = 0;
                if (item->data(Qt::UserRole + 1) == 777) {
                    MyGraphicsEllipseItem * it_el = static_cast <MyGraphicsEllipseItem *> (other);
                    item_size = it_el->rect().width();

                } else if (other->data(Qt::UserRole + 1) == 111) {
                    MyGraphicsRectItem * it_rect = static_cast <MyGraphicsRectItem *> (other);
                    item_size = it_rect->rect().width();
                }

                int other_size = 0;
                if (other->data(Qt::UserRole + 1) == 777) {
                    MyGraphicsEllipseItem * ot_el = static_cast <MyGraphicsEllipseItem *> (other);
                    other_size = ot_el->rect().width();

                } else if (other->data(Qt::UserRole + 1) == 111) {
                    MyGraphicsRectItem * ot_rect = static_cast <MyGraphicsRectItem *> (other);
                    other_size = ot_rect->rect().width();
                }

                if (item_size > other_size) {
                    scene.removeItem(other);
//                    delete other;

                    item->setScale(1.1); // увеличиваем на 10%
                } else {
                    scene.removeItem(item);
//                    delete item;

                    other->setScale(1.1); // увеличиваем на 10%
                }
            }
            return;
        }
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    resize(500, 500);
    ui->graphicsView->resize(size());

    qsrand(QTime::currentTime().msec());

    int m = 5; // квадраты
    int n = 3; // кругов

    for (int i = 0; i < m; i++) {
        QGraphicsRectItem * rectItem = new QGraphicsRectItem(); // создание класс Квадрат
        // случайный цвет в rgb
        rectItem->setBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
        int x = qrand() % (ui->graphicsView->width() - 100);
        int y = qrand() % (ui->graphicsView->height() - 100);
        int s = (qrand() % 30) + 5; // размер от 10 до 99
        rectItem->setRect(x, y, s, s); // установка положения и размера
        scene.addItem(rectItem); // добавление на сцену
    }

    for (int i = 0; i < m; i++) {
        QGraphicsEllipseItem * ellipseItem = new QGraphicsEllipseItem(); // создание класс Круг
        // случайный цвет в rgb
        ellipseItem->setBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
        int x = qrand() % (ui->graphicsView->width() / 2);
        int y = qrand() % (ui->graphicsView->height() / 2);
        int s = (qrand() % 30) + 5; // размер от 10 до 99
        ellipseItem->setRect(x, y, s, s); // установка положения и размера
        scene.addItem(ellipseItem); // добавление на сцену
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include <QGraphicsRectItem>

class MyGraphicsRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public slots:
    QRectF geometry() { return this->rect(); }
    void setGeometry(QRectF r) { this->setRect(r); }
};

class MyGraphicsEllipseItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public slots:
    QRectF geometry() { return this->rect(); }
    void setGeometry(QRectF r) { this->setRect(r); }
};


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;

    QList <MyGraphicsRectItem * > rect_items;
    QList <MyGraphicsEllipseItem * > ellipse_items;
};

#endif // MAINWINDOW_H

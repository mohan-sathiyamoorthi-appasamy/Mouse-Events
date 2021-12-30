#pragma once

#define _USE_MATH_DEFINES

#include <QtWidgets/QMainWindow>
#include "ui_mouseEventsQt.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QLabel>
#include <QDir>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include<fstream>
#include<sstream>
#include <iostream>
#include <conio.h>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class mouseEventsQt : public QMainWindow
{
    Q_OBJECT

public:
    mouseEventsQt(QWidget *parent = Q_NULLPTR);

    void CSVStackList(QString csvPath);
    void ImageStackList(QString imagePath);
    //void readImage(int);
    void readCSV(string filename);

    string fileName, csvName;
    QString enfacePath, imagePath, csvPath;
    QStringList imagestackList, csvstackList;

public slots:
    void readImage(int);
    void receivePosition(float);

private slots:


private:
    Ui::mouseEventsQtClass ui;
};

class customGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    void graphicsLineItem();
    void HighlightLayer(int);
    void removeEllipse(int);

    QList<QGraphicsLineItem*> vect1;
    QList<QGraphicsLineItem*> vect2;
    QList<QGraphicsLineItem*> vect3;
    QList<QGraphicsLineItem*> vect4;
    QList<QGraphicsLineItem*> vect5;
    QList<QGraphicsLineItem*> vect6;
    QList<QGraphicsLineItem*> vect7;
    QList<QGraphicsLineItem*> vect8;

    QList <QGraphicsEllipseItem*> ellipse1;
    QList <QGraphicsEllipseItem*> ellipse2;
    QList <QGraphicsEllipseItem*> ellipse3;
    QList <QGraphicsEllipseItem*> ellipse4;
    QList <QGraphicsEllipseItem*> ellipse5;
    QList <QGraphicsEllipseItem*> ellipse6;
    QList <QGraphicsEllipseItem*> ellipse7;
    QList <QGraphicsEllipseItem*> ellipse8;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    QGraphicsPixmapItem* item1;
    QGraphicsLineItem* lineItem1;
    QGraphicsLineItem* lineItem2;
    QGraphicsLineItem* lineItem3;
    QGraphicsLineItem* lineItem4;
    QGraphicsLineItem* lineItem5;
    QGraphicsLineItem* lineItem6;
    QGraphicsLineItem* lineItem7;
    QGraphicsLineItem* lineItem8;

    QLine* line;

    QGraphicsEllipseItem* EllipseItem1;
    QGraphicsEllipseItem* EllipseItem2;
    QGraphicsEllipseItem* EllipseItem3;
    QGraphicsEllipseItem* EllipseItem4;
    QGraphicsEllipseItem* EllipseItem5;
    QGraphicsEllipseItem* EllipseItem6;
    QGraphicsEllipseItem* EllipseItem7;
    QGraphicsEllipseItem* EllipseItem8;
};


class customMouseEvent : public QScrollArea
{
    Q_OBJECT

public:
    explicit customMouseEvent(int x, int y, bool move, QWidget* parent = 0);
    ~customMouseEvent();

    int x, y, Totalimg;
    bool moveline, mousewheel;
    Mat mat_image;

    void graphicsSetScene(Mat mat_image);
    void imageScroll();
    //float map(float x, float in_min, float in_max, float out_min, float out_max);
    QPixmap pixMap(Mat image);
    void wheelEvent(QWheelEvent* event);

public slots:
    //void receivelineposition_Y(float y);

signals:
    void sendmousewheelvalue(int x);

private:
    QGraphicsView* graphics;
    QGraphicsPixmapItem* item;
};

class customGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit customGraphicsView(QString Filepath1, int x, int y, bool moveh, bool movev, QWidget* parent = 0);
    ~customGraphicsView();

    int width, height;
    bool mousewheel, movelineh, movelinev;
    bool HLinePressed, VLinePressed;
    float val = 0.5;
    float Vline_pos, Hline_pos;
    int MPX = 0, MPY = 0;
    int MMX, MMY;
    QString enface_img_path;

    QPixmap enfaceimg;
    QGraphicsPixmapItem* pixItem;

    QGraphicsScene* Scene;
    void loadImage();
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    void setCurrentImage(QPixmap img);
    float VLineUpdate(float y);
    float HLineUpdate(float x);

signals:
    void sendHLineposition(float);
    void sendVLineposition(float);

public slots:
    void receivemousewheelvalue_H(int val);
};

class customGraphicsLine : public QGraphicsLineItem
{
public:
    explicit  customGraphicsLine(QColor lineColor, QGraphicsItem* parent = nullptr);

    qreal outlineWidth() const;
    void setOutlineWidth(qreal outlineWidth);

    QColor outlineColor() const;
    void setOutlineColor(const QColor& outlineColor);

    void paint(QPainter* apainter, const QStyleOptionGraphicsItem* aoption, QWidget* widget) override;
    void updateGeometry();

protected:

private:
    qreal m_outlineWidth;
    QColor m_outlineColor;
    QColor m_lineColor;
};
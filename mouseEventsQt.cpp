#include "mouseEventsQt.h"

customGraphicsLine* HLineItem;
customGraphicsLine* VLineItem;
customGraphicsView* gvlmt;
customMouseEvent* saH;
mouseEventsQt* mouse;

customGraphicsScene* scene;
vector< vector<int> > all_data;
vector< vector<int> > newPointsData;

int value = 0, currentimg = 63, mousewheelvalue = 63;

mouseEventsQt::mouseEventsQt(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    enfacePath = "D:/Python_Projects/Python_OCTA_Changed";
    imagePath = "E:/Output/CompositeImage";
    csvPath = "E:/Output/Data_CSV";

    CSVStackList(csvPath);
    ImageStackList(imagePath);

    gvlmt = new customGraphicsView(enfacePath, ui.graphicsView->width(), ui.graphicsView->height(), true, false, ui.graphicsView);
    saH = new customMouseEvent(ui.scrollArea->width(), ui.scrollArea->height(), true);
    ui.scrollArea->setWidget(saH);

    connect(gvlmt, SIGNAL(sendHLineposition(float)), SLOT(receivePosition(float)));
    connect(saH, SIGNAL(sendmousewheelvalue(int)), gvlmt, SLOT(receivemousewheelvalue_H(int)));
    connect(saH, SIGNAL(sendmousewheelvalue(int)), SLOT(readImage(int)));

    gvlmt->loadImage();
    readImage(currentimg);
}

void mouseEventsQt::CSVStackList(QString csvPath)
{
    QString folderpath = csvPath + "/";
    if (!folderpath.isEmpty())
    {
        QDir dir(folderpath);
        QStringList filter;
        filter << QLatin1String("*.csv");
        dir.setNameFilters(filter);
        QFileInfoList filelistinfo = dir.entryInfoList();

        foreach(const QFileInfo & fileinfo, filelistinfo)
        {
            csvstackList << fileinfo.absoluteFilePath();
        }
    }
}

void mouseEventsQt::ImageStackList(QString imagePath)
{
    QString folderpath = imagePath + "/";
    if (!folderpath.isEmpty())
    {
        QDir dir(folderpath);
        QStringList filter;
        filter << QLatin1String("*.tif");
        dir.setNameFilters(filter);
        QFileInfoList filelistinfo = dir.entryInfoList();

        foreach(const QFileInfo & fileinfo, filelistinfo)
        {
            imagestackList << fileinfo.absoluteFilePath();
        }
    }
}

void mouseEventsQt::readCSV(string filename)
{
    all_data.clear();
    newPointsData.clear();

    ifstream inputfile(filename);

    string current_line;
    while (getline(inputfile, current_line))
    {
        vector<int> values;
        stringstream temp(current_line);
        string single_value;

        while (getline(temp, single_value, ','))
        {
            values.push_back(atoi(single_value.c_str()));
        }

        all_data.push_back(values);
        newPointsData.push_back(values);
    }
}

void mouseEventsQt::readImage(int val)
{
    if (imagestackList.count() > 0)
    {
        //qDebug() << currentimg;
        QString QfileName = imagestackList.at(val);
        QString QcsvName = csvstackList.at(val);
        
        fileName = QfileName.toStdString();
        csvName = QcsvName.toStdString();

        readCSV(csvName);
        Mat image = imread(fileName);
        //imshow("Image", image);
        saH->graphicsSetScene(image);
    }
    else
    {
        qDebug() << "No Data";
    }
}

void mouseEventsQt::receivePosition(float x)
{
    currentimg = x * 128;
    mousewheelvalue = currentimg;
    readImage(currentimg);
}

//GraphicsScene
void customGraphicsScene::HighlightLayer(int i1)
{
    value = i1;

    switch (i1)
    {
    case 0:
        ellipse1.clear();
        for (int i = 0; i < 500; i += 25)
        {
            //cout << all_data[i1][i] << endl;
            EllipseItem1 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem1->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem1->setBrush(QBrush(Qt::green, Qt::SolidPattern));

            EllipseItem1->setVisible(true);
            EllipseItem1->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem1->setData(i, i1);
            scene->addItem(EllipseItem1);
            //qDebug() << EllipseItem1;
            ellipse1.append(EllipseItem1);
        }

        break;

    case 1:
        ellipse2.clear();
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem2 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem2->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem2->setBrush(QBrush(Qt::red, Qt::SolidPattern));
            EllipseItem2->setVisible(true);
            EllipseItem2->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem2->setData(i, i1);
            scene->addItem(EllipseItem2);
            ellipse2.append(EllipseItem2);
        }
        break;

    case 2:
        ellipse3.clear();
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem3 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem3->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem3->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            EllipseItem3->setVisible(true);
            EllipseItem3->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem3->setData(i, i1);
            scene->addItem(EllipseItem3);
            ellipse3.append(EllipseItem3);
        }
        break;

    case 3:
        ellipse4.clear();
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem4 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem4->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem4->setBrush(QBrush(Qt::gray, Qt::SolidPattern));
            EllipseItem4->setVisible(true);
            EllipseItem4->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem4->setData(i, i1);
            scene->addItem(EllipseItem4);
            ellipse4.append(EllipseItem4);
        }
        break;

    case 4:
        ellipse5.clear();
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem5 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem5->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem5->setBrush(QBrush(Qt::cyan, Qt::SolidPattern));
            EllipseItem5->setVisible(true);
            EllipseItem5->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem5->setData(i, i1);
            scene->addItem(EllipseItem5);
            ellipse5.append(EllipseItem5);
        }
        break;

    case 5:
        ellipse6.clear();
        //cout << "sixthlayer" << endl;
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem6 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem6->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem6->setBrush(QBrush(Qt::magenta, Qt::SolidPattern));
            EllipseItem6->setVisible(true);
            EllipseItem6->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem6->setData(i, i1);
            scene->addItem(EllipseItem6);
            ellipse6.append(EllipseItem6);
        }
        break;

    case 6:
        ellipse7.clear();
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem7 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem7->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem7->setBrush(QBrush(Qt::darkYellow, Qt::SolidPattern));
            EllipseItem7->setVisible(true);
            EllipseItem7->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem7->setData(i, i1);
            scene->addItem(EllipseItem7);
            ellipse7.append(EllipseItem7);
        }
        break;

    case 7:
        ellipse8.clear();
        for (int i = 0; i < 500; i += 25)
        {
            EllipseItem8 = new QGraphicsEllipseItem(i - 5, all_data[i1][i] - 5, 10, 10);
            EllipseItem8->setPen(QPen(QColor(242, 235, 226), 1.5, Qt::SolidLine));
            EllipseItem8->setBrush(QBrush(Qt::darkGreen, Qt::SolidPattern));
            EllipseItem8->setVisible(true);
            EllipseItem8->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsMovable);
            EllipseItem8->setData(i, i1);
            scene->addItem(EllipseItem8);
            ellipse8.append(EllipseItem8);
        }
        break;

    default:

        break;
    }
}

void customGraphicsScene::removeEllipse(int val1)
{
    //qDebug() << "val1";

    switch (val1)
    {
    case 0:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse1[i]);
        }
        //ellipse1.clear();
        break;

    case 1:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse2[i]);
        }
        //ellipse2.clear();
        break;

    case 2:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse3[i]);
        }
        //ellipse3.clear();
        break;

    case 3:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse4[i]);
        }
        //ellipse4.clear();
        break;

    case 4:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse5[i]);
        }
        //ellipse5.clear();
        break;

    case 5:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse6[i]);
        }
        //ellipse6.clear();
        break;

    case 6:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse7[i]);
        }
        //ellipse7.clear();
        break;

    case 7:
        for (int i = 0; i < 20; i++)
        {
            scene->removeItem(ellipse8[i]);
        }
        //ellipse8.clear();
        break;

    default:

        break;
    }
}

void customGraphicsScene::graphicsLineItem()
{
    vect1.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem1 = new QGraphicsLineItem(i, all_data[0][i], (i + 25), all_data[0][(i + 25)]);
        if ((i + 25) < 475)
            lineItem1 = new QGraphicsLineItem(i, all_data[0][i], (i + 25), all_data[0][(i + 25)]);
        else
            lineItem1 = new  QGraphicsLineItem(i, all_data[0][i], (i + 25), all_data[0][(i + 24)]);
        lineItem1->setPen(QPen(Qt::green, 1, Qt::SolidLine));
        lineItem1->setVisible(true);
        lineItem1->setData(i, "LineBoundary0");
        //lineItem1->setFlags( QGraphicsLineItem::ItemIsMovable);
        scene->addItem(lineItem1);
        vect1.append(lineItem1);
    }

    vect2.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem2 = new QGraphicsLineItem(i, all_data[1][i], (i + 25), all_data[1][(i + 25)]);
        if ((i + 25) < 475)
            lineItem2 = new QGraphicsLineItem(i, all_data[1][i], (i + 25), all_data[1][(i + 25)]);
        else
            lineItem2 = new  QGraphicsLineItem(i, all_data[1][i], (i + 25), all_data[1][(i + 24)]);
        lineItem2->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        lineItem2->setVisible(true);
        lineItem2->setData(i, "LineBoundary1");
        // lineItem2->setFlags(QGraphicsLineItem::ItemIsMovable);
        scene->addItem(lineItem2);
        vect2.append(lineItem2);
    }

    vect3.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem3 = new QGraphicsLineItem(i, all_data[2][i], (i + 25), all_data[2][(i + 25)]);
        if ((i + 25) < 475)
            lineItem3 = new QGraphicsLineItem(i, all_data[2][i], (i + 25), all_data[2][(i + 25)]);
        else
            lineItem3 = new  QGraphicsLineItem(i, all_data[2][i], (i + 25), all_data[2][(i + 24)]);
        lineItem3->setPen(QPen(Qt::blue, 1, Qt::SolidLine));
        lineItem3->setData(i, "LineBoundary2");
        // lineItem3->setFlags(QGraphicsLineItem::ItemIsMovable);
        scene->addItem(lineItem3);
        vect3.append(lineItem3);
    }

    vect4.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem4 = new QGraphicsLineItem(i, all_data[3][i], (i + 25), all_data[3][(i + 25)]);
        if ((i + 25) < 475)
            lineItem4 = new QGraphicsLineItem(i, all_data[3][i], (i + 25), all_data[3][(i + 25)]);
        else
            lineItem4 = new  QGraphicsLineItem(i, all_data[3][i], (i + 25), all_data[3][(i + 24)]);
        lineItem4->setPen(QPen(Qt::gray, 1, Qt::SolidLine));
        lineItem4->setData(i, "LineBoundary3");
        scene->addItem(lineItem4);
        vect4.append(lineItem4);
    }

    vect5.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem5 = new QGraphicsLineItem(i, all_data[4][i], (i + 25), all_data[4][(i + 25)]);
        if ((i + 25) < 475)
            lineItem5 = new QGraphicsLineItem(i, all_data[4][i], (i + 25), all_data[4][(i + 25)]);
        else
            lineItem5 = new  QGraphicsLineItem(i, all_data[4][i], (i + 25), all_data[4][(i + 24)]);
        lineItem5->setPen(QPen(Qt::cyan, 1, Qt::SolidLine));
        lineItem5->setData(i, "LineBoundary4");
        scene->addItem(lineItem5);
        vect5.append(lineItem5);
    }

    vect6.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem6 = new QGraphicsLineItem(i, all_data[5][i], (i + 25), all_data[5][(i + 25)]);
        if ((i + 25) < 475)
            lineItem6 = new QGraphicsLineItem(i, all_data[5][i], (i + 25), all_data[5][(i + 25)]);
        else
            lineItem6 = new  QGraphicsLineItem(i, all_data[5][i], (i + 25), all_data[5][(i + 24)]);
        lineItem6->setPen(QPen(Qt::magenta, 1, Qt::SolidLine));
        lineItem6->setData(i, "LineBoundary5");
        scene->addItem(lineItem6);
        vect6.append(lineItem6);
    }

    vect7.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem7 = new QGraphicsLineItem(i, all_data[6][i], (i + 25), all_data[6][(i + 25)]);
        if ((i + 25) < 475)
            lineItem7 = new QGraphicsLineItem(i, all_data[6][i], (i + 25), all_data[6][(i + 25)]);
        else
            lineItem7 = new  QGraphicsLineItem(i, all_data[6][i], (i + 25), all_data[6][(i + 24)]);
        lineItem7->setPen(QPen(Qt::darkGreen, 1, Qt::SolidLine));
        lineItem7->setData(i, "LineBoundary6");
        scene->addItem(lineItem7);
        vect7.append(lineItem7);
    }

    vect8.clear();
    for (int i = 0; i < 500; i += 25)
    {
        //lineItem8 = new QGraphicsLineItem(i, all_data[7][i], (i + 25), all_data[7][(i + 25)]);
        if ((i + 25) < 475)
            lineItem8 = new QGraphicsLineItem(i, all_data[7][i], (i + 25), all_data[7][(i + 25)]);
        else
            lineItem8 = new  QGraphicsLineItem(i, all_data[7][i], (i + 25), all_data[7][(i + 24)]);
        lineItem8->setPen(QPen(Qt::darkRed, 1, Qt::SolidLine));
        lineItem8->setData(i, "LineBoundary7");
        scene->addItem(lineItem8);
        vect8.append(lineItem8);
    }
}

void customGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF mousePosition = event->scenePos();
    QGraphicsItem* pItem = QGraphicsScene::itemAt(QPointF(mousePosition.x(), mousePosition.y()), QTransform());
    if (pItem == NULL)
    {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    if (pItem->isSelected() == false)
    {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    QList<QGraphicsItem*> items = selectedItems();
    //cout << "items count " << items.count() << endl;
    for (int i = 0; i < items.count(); i++)
    {
        for (int j = 0; j < 500; j += 25)
        {
            if (!items[i]->data(j).toString().isEmpty())
            {
                //qDebug() << " j : " << j << items[i]->data(j).toString();
                int x = items[i]->boundingRect().x() + items[i]->pos().x();
                int y = items[i]->boundingRect().y() + items[i]->pos().y();

                if (items[i]->data(j) == 0)
                {
                    items[i]->setPos(items[i]->pos());
                    //qDebug() << "items" << endl;
                    int l1x1 = j;
                    int l1y1 = all_data[0][j];
                    int l1x2 = vect1[j / 25]->line().x2();
                    int l1y2 = vect1[j / 25]->line().y2();

                    //qDebug() << "j : " << l1x1 << l1y1 << l1x2 << l1y2;

                    int l2x1 = vect1[(j - 1) / 25]->line().x1();
                    int l2y1 = vect1[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[0][j];
                    //qDebug() << "j1 : " << l2x1;

                    vect1[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect1[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);

                    newPointsData[0][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                else if (items[i]->data(j) == 1)
                {
                    //cout << "Second Layer" << endl;
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[1][j];
                    int l1x2 = vect2[j / 25]->line().x2();
                    int l1y2 = vect2[j / 25]->line().y2();

                    int l2x1 = vect2[(j - 1) / 25]->line().x1();
                    int l2y1 = vect2[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[1][j];

                    vect2[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect2[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[1][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                else if (items[i]->data(j) == 2)
                {
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[2][j];
                    int l1x2 = vect3[j / 25]->line().x2();
                    int l1y2 = vect3[j / 25]->line().y2();

                    int l2x1 = vect3[(j - 1) / 25]->line().x1();
                    int l2y1 = vect3[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[2][j];

                    vect3[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect3[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[2][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                else if (items[i]->data(j) == 3)
                {
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[3][j];
                    int l1x2 = vect4[j / 25]->line().x2();
                    int l1y2 = vect4[j / 25]->line().y2();

                    int l2x1 = vect4[(j - 1) / 25]->line().x1();
                    int l2y1 = vect4[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[3][j];

                    vect4[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect4[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[3][j] = l1y1 + items[i]->pos().y(); // Right Side
                }


                else if (items[i]->data(j) == 4)
                {
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[4][j];
                    int l1x2 = vect5[j / 25]->line().x2();
                    int l1y2 = vect5[j / 25]->line().y2();

                    int l2x1 = vect5[(j - 1) / 25]->line().x1();
                    int l2y1 = vect5[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[4][j];

                    vect5[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect5[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[4][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                else if (items[i]->data(j) == 5)
                {
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[5][j];
                    int l1x2 = vect6[j / 25]->line().x2();
                    int l1y2 = vect6[j / 25]->line().y2();

                    int l2x1 = vect6[(j - 1) / 25]->line().x1();
                    int l2y1 = vect6[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[5][j];

                    vect6[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect6[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[5][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                else if (items[i]->data(j) == 6)
                {
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[6][j];
                    int l1x2 = vect7[j / 25]->line().x2();
                    int l1y2 = vect7[j / 25]->line().y2();

                    int l2x1 = vect7[(j - 1) / 25]->line().x1();
                    int l2y1 = vect7[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[6][j];

                    vect7[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect7[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[6][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                else if (items[i]->data(j) == 7)
                {
                    //cout << "Last Layer" << endl;
                    items[i]->setPos(items[i]->pos());

                    int l1x1 = j;
                    int l1y1 = all_data[7][j];
                    int l1x2 = vect8[j / 25]->line().x2();
                    int l1y2 = vect8[j / 25]->line().y2();

                    int l2x1 = vect8[(j - 1) / 25]->line().x1();
                    int l2y1 = vect8[(j - 1) / 25]->line().y1();
                    int l2x2 = j;
                    int l2y2 = all_data[7][j];

                    vect8[(j - 1) / 25]->setLine(l2x1, l2y1, l2x2 + items[i]->pos().x(), l2y2 + items[i]->pos().y());
                    vect8[j / 25]->setLine(l1x1 + items[i]->pos().x(), l1y1 + items[i]->pos().y(), l1x2, l1y2);
                    newPointsData[7][j] = l1y1 + items[i]->pos().y(); // Right Side
                }

                QGraphicsScene::mouseMoveEvent(event);
            }
        }
    }
}

//ScrollArea
customMouseEvent::customMouseEvent(int xx, int yy, bool move, QWidget* parent) : QScrollArea(parent)
{
    //currentimg = 64;
    //Totalimg = currentimg * 2;
    x = xx;
    y = yy;
    moveline = move;
    mousewheel = false;
    //mousewheelvalue = currentimg;

    this->setFixedWidth(xx);
    this->setFixedHeight(yy);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);

    graphics = new QGraphicsView();

    graphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphics->setFixedWidth(this->width());
    graphics->setFixedHeight(this->height());
    graphics->setAlignment(Qt::AlignCenter);

    this->setWidget(graphics);
    this->installEventFilter(this);
}

void customMouseEvent::graphicsSetScene(Mat mat_image)
{
    item = new QGraphicsPixmapItem();
    scene = new customGraphicsScene();

    item->setPixmap(pixMap(mat_image));
    scene->addItem(item);

    graphics->setScene(scene);
    scene->graphicsLineItem();
    scene->HighlightLayer(value);
}

void customMouseEvent::imageScroll()
{
    //qDebug() << "mousewheelvalue1" << mousewheelvalue;
    //mouse = new mouseEventsQt();
    //qDebug() << "mousewheelvalue2" << mousewheelvalue;
    //mouse->readImage();
}

void customMouseEvent::wheelEvent(QWheelEvent* event)
{
    mousewheel = true;

    if (event->delta() > 0)
    {
        if (mousewheelvalue < 127)
        {
            mousewheelvalue++;
            currentimg = mousewheelvalue;
            //imageScroll();
            emit sendmousewheelvalue(mousewheelvalue);
        }
    }
    else
    {
        if (mousewheelvalue > 0)
        {
            mousewheelvalue--;
            currentimg = mousewheelvalue;
            //imageScroll();
            emit sendmousewheelvalue(mousewheelvalue);
        }
    }
}

QPixmap customMouseEvent::pixMap(Mat image)
{
    //imshow("Image", image);
    cvtColor(image, image, COLOR_BGR2RGB);
    QPixmap octimg_new = QPixmap::fromImage(QImage((uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888));
    return octimg_new;
}

//void customMouseEvent::receivelineposition_Y(float y)
//{
//    currentimg = y * 128;
//    mousewheelvalue = currentimg;
//    imageScroll();
//}

customMouseEvent::~customMouseEvent()
{

}

//GraphicsView
customGraphicsView::customGraphicsView(QString Filepath1, int xx, int yy, bool moveh, bool movev, QWidget* parent) : QGraphicsView(parent)
{
    width = xx;
    height = yy;
    movelineh = moveh;
    movelinev = movev;
    mousewheel = false;
    //mousewheelvalue = 5;

    enface_img_path = Filepath1;

    this->setFixedWidth(width);
    this->setFixedHeight(height);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    HLineItem = new customGraphicsLine(QColor(23, 179, 219));
    HLineItem->setCursor(Qt::SizeHorCursor);
    VLineItem = new customGraphicsLine(QColor(214, 96, 255));
    VLineItem->setCursor(Qt::SizeVerCursor);

    Scene = new QGraphicsScene();
    this->setScene(Scene);

    pixItem = new QGraphicsPixmapItem(enfaceimg);
    Scene->addItem(pixItem);

    if (movelineh == true)
    {
        HLineItem->setLine(width-5, height/2, 5, height/2);
        HLineItem->setData(0, "HLine");
        HLineItem->setCursor(Qt::SizeHorCursor);
        Scene->addItem(HLineItem);
    }
    if (movelinev == true)
    {
        VLineItem->setLine(width/2, 5, width/2, height-5);
        VLineItem->setData(0, "VLine");
        VLineItem->setCursor(Qt::SizeVerCursor);
        Scene->addItem(VLineItem);
    }
    //val = 0.5;

    this->setRenderHint(QPainter::Antialiasing);
}

void customGraphicsView::loadImage()
{
    QString enf_imagepath = enface_img_path + "/EnfaceImage.tif";
    enfaceimg.load(enf_imagepath);
    pixItem->setPixmap(enfaceimg.scaled(width, height));
}

void customGraphicsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsItem* item = this->itemAt(event->pos().x(), event->pos().y());
    if (item->data(0).toString() == "HLine")
    {
        HLinePressed = true;
    }
    if (item->data(0).toString() == "VLine")
    {
        VLinePressed = true;
    }
    if (event->button() == Qt::LeftButton)
    {
        MPX = event->pos().x();
        MPY = event->pos().y();
    }
}

void customGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    HLinePressed = false;
    VLinePressed = false;
}

void customGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (HLinePressed)
    {
        if (event->pos().y() > 0 && event->pos().y() < height)
        {
            Hline_pos = event->pos().y();
            emit sendHLineposition(HLineUpdate(Hline_pos));
        }
    }
    if (VLinePressed)
    {
        if (event->pos().x() > 0 && event->pos().x() < width)
        {
            Vline_pos = event->pos().x();
            emit sendVLineposition(VLineUpdate(Vline_pos));
        }
    }
    QMouseEvent* me = static_cast<QMouseEvent*>(event);
    QPoint coord(event->pos().x(), event->pos().y());
    QRect geo = this->geometry();
    if (me->buttons() == Qt::LeftButton)
    {
        if (coord.x() <= geo.width() && coord.x() >= 0 && coord.y() <= geo.height() && coord.y() >= 0)
        {
            MMX = event->pos().x();
            MMY = event->pos().y();
        }
    }
}

void customGraphicsView::receivemousewheelvalue_H(int val)
{
    Hline_pos = (float)(height * val ) / 128 ;
    HLineUpdate(Hline_pos); 
}

float customGraphicsView::HLineUpdate(float val)
{

    HLineItem->setLine(width-5, val, 5, val);
    update();
    float h_position = (float)val / (float)height;
    //Hline_pos = h_position * 128;
    return h_position;
}

float customGraphicsView::VLineUpdate(float val)
{
    VLineItem->setLine(val, 5, val, width-5);
    update();
    float v_position = (float)val / (float)width;
    //Vline_pos = v_position * 128;
    return v_position;
}

void customGraphicsView::setCurrentImage(QPixmap img)
{
    pixItem->setPixmap(img);
}

customGraphicsView::~customGraphicsView()
{

}

//GraphicsViewLineItem
customGraphicsLine::customGraphicsLine(QColor lineColor, QGraphicsItem* parent) : QGraphicsLineItem(parent), m_outlineWidth(1), m_outlineColor(Qt::red)
{
    m_lineColor = lineColor;
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

void customGraphicsLine::paint(QPainter* aPainter, const QStyleOptionGraphicsItem* aOption, QWidget* aWidget = nullptr)
{
    QLineF cLine = line();
    aPainter->setRenderHint(QPainter::Antialiasing);
    aPainter->setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
    aPainter->drawLine(cLine);
    qreal lineAngle = cLine.angle();
    const qreal radius = 3.0;
    QLineF head1 = cLine;
    head1.setAngle(lineAngle + 30);
    head1.setLength(9);
    QLineF head2 = cLine;
    head2.setAngle(lineAngle - 30);
    head2.setLength(9);
    aPainter->drawLine(head1);
    aPainter->drawLine(head2);
    aPainter->setPen(QPen(m_lineColor, 2.5, Qt::SolidLine, Qt::RoundCap));
    aPainter->drawLine(cLine);
    aPainter->drawLine(head1);
    aPainter->drawLine(head2);
}

qreal customGraphicsLine::outlineWidth() const
{
    return m_outlineWidth;
}

void customGraphicsLine::setOutlineWidth(qreal outlineWidth)
{
    m_outlineWidth = outlineWidth;
}

QColor customGraphicsLine::outlineColor() const
{
    return m_outlineColor;
}

void customGraphicsLine::setOutlineColor(const QColor& outlineColor)
{
    m_outlineColor = outlineColor;
}

void customGraphicsLine::updateGeometry()
{
    this->prepareGeometryChange();
}

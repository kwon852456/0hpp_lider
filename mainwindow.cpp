#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

#include <3vmw9.hpp>

using namespace rv2;

extern QPolarChart *p_chart;
extern QString portNum;

QT_CHARTS_USE_NAMESPACE


#define COMPORT "COM5"


MainWindow::MainWindow(QWidget *parent)
    : QChartView(parent)
{

    port = new QSerialPort();
    port->setPortName(portNum);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    refresh_timer = new QTimer(this);


    int width = 2;

    Qt::PenStyle style = Qt::PenStyle(Qt::SolidLine);
    Qt::PenCapStyle cap = Qt::PenCapStyle(Qt::RoundCap);
    Qt::PenJoinStyle join = Qt::PenJoinStyle(Qt::RoundJoin);

    myPen = QPen(Qt::red, width, style, cap, join);

    if(!port->open(QIODevice::ReadWrite)){
       qDebug() << "Serial connect fialed" << endl;
    }

    angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(false);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    //p_chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%d");
    //p_chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);


    series1 = new QScatterSeries();    
    series1->setMarkerSize(6);
    series1->setColor(QColor::fromRgb(255,0,0));
    series1->setPen(QPen());



    connect(port, &QSerialPort::readyRead, this, &MainWindow::angl_sri);
    connect(refresh_timer, &QTimer::timeout, this, &MainWindow::refreshChart);

    refresh_timer->start(1000);


}

void MainWindow::refreshChart(){


    series1->replace(points);
    qDebug() <<"endSeri" << endl;

    p_chart->removeSeries(series1);
    p_chart->addSeries(series1);

    //p_chart->removeAllSeries(series1);
    qDebug() <<"removeSeries" << endl;
    //series1->clear();


    qDebug() <<"addSeri" << endl;

    points.clear();


}

void MainWindow::angl_sri(){
    qDebug() << " sri received..!" << endl;

    QByteArray dataFromSri = port -> read(4);
    y::p yDataFromSri = reinterpret_cast<y::p>(dataFromSri.data());


    y2::u a2, b2;
    a2.t2[0] = yDataFromSri[1];
    a2.t2[1] = yDataFromSri[0];
    b2.t2[0] = yDataFromSri[3];
    b2.t2[1] = yDataFromSri[2];

    points.push_back(QPointF(a2.h1,b2.h1));


    qDebug() << "degree" << a2.h1 << "distance" << b2.h1 << "size" << points.size() << endl;


}

#include "mainwindow.h"
#include <QApplication>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>
#include <QPalette>

QT_CHARTS_USE_NAMESPACE
QPolarChart *chart;

int main(int argc, char *argv[])
{
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    QApplication a(argc, argv);

       const qreal angularMin = 0;
       const qreal angularMax = 360;

       const qreal radialMin = 0;
       const qreal radialMax = 100;

       QScatterSeries *series1 = new QScatterSeries();
       series1->setName("scatter");


       series1->append(0,0);
       series1->append(50,50);
       series1->append(100,100);
       series1->append(180,100);

       series1->setMarkerSize(1);
       series1->setColor(QColor::fromRgb(255,0,0));

       int width = 2;
       Qt::PenStyle style = Qt::PenStyle(Qt::SolidLine);
       Qt::PenCapStyle cap = Qt::PenCapStyle(Qt::RoundCap);
       Qt::PenJoinStyle join = Qt::PenJoinStyle(Qt::RoundJoin);

       series1->setPen(QPen(Qt::red, width, style, cap, join));

       chart = new QPolarChart();
       chart->setBackgroundVisible(false);
       chart->setAutoFillBackground(true);
       chart->setPalette(pal);
       chart->addSeries(series1);



       chart->setTitle("Use arrow keys to scroll, +/- to zoom, and space to switch chart type.");

       QValueAxis *angularAxis = new QValueAxis();
       angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
       angularAxis->setLabelFormat("%.1f");
       angularAxis->setShadesVisible(false);
       angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
       chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

       QValueAxis *radialAxis = new QValueAxis();
       radialAxis->setTickCount(9);
       radialAxis->setLabelFormat("%d");
       chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

       series1->attachAxis(angularAxis);
       series1->attachAxis(radialAxis);


       radialAxis->setRange(radialMin, radialMax);
       angularAxis->setRange(angularMin, angularMax);

       MainWindow *chartView = new MainWindow();
       chartView->setAutoFillBackground(true);
       chartView->setPalette(pal);

       chartView->setChart(chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       QMainWindow window;
       window.setCentralWidget(chartView);

       window.resize(800, 600);

       window.setAutoFillBackground(true);
       window.setPalette(pal);


       window.show();


    return a.exec();
}

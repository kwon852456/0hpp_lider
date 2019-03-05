#include "mainwindow.h"
#include <QApplication>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QInputDialog>

QT_CHARTS_USE_NAMESPACE

QPolarChart *p_chart;
QString portNum = "";

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    bool ok;
       // Ask for birth date as a string.
       portNum = QInputDialog::getText(0, "Input dialog","portNum ex)COM5:", QLineEdit::Normal,"", &ok);
       if (ok && !portNum.isEmpty()) {

       }

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);


       const qreal angularMin = 0;
       const qreal angularMax = 360;

       const qreal radialMin = 0;
       const qreal radialMax = 360;

       p_chart = new QPolarChart();
       p_chart->setBackgroundVisible(false);
       p_chart->setAutoFillBackground(true);
       p_chart->setPalette(pal);




       p_chart->setTitle("Use arrow keys to scroll, +/- to zoom, and space to switch chart type.");

       QValueAxis *angularAxis = new QValueAxis();
       angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
       angularAxis->setLabelFormat("%.1f");
       angularAxis->setShadesVisible(false);
       angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
       p_chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

       QValueAxis *radialAxis = new QValueAxis();
       radialAxis->setTickCount(9);
       radialAxis->setLabelFormat("%d");
       p_chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);


       radialAxis->setRange(radialMin, radialMax);
       angularAxis->setRange(angularMin, angularMax);

       MainWindow *chartView = new MainWindow();
       chartView->setAutoFillBackground(true);
       chartView->setPalette(pal);

       chartView->setChart(p_chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       QMainWindow window;
       window.setCentralWidget(chartView);

       window.resize(800, 600);

       window.setAutoFillBackground(true);
       window.setPalette(pal);

       window.show();

    return a.exec();
}

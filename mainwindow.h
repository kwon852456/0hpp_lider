#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>
#include "QtSerialPort/QSerialPort"

#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>
#include <QPalette>
#include <QTimer>

QT_CHARTS_USE_NAMESPACE



namespace Ui {
class MainWindow;
}

class MainWindow : public QChartView
{
public:
    MainWindow(QWidget *parent = 0);
    void angl_sri();

    QSerialPort* port;
    QPen myPen;
    QScatterSeries *series1;
    QTimer* refresh_timer;
    QValueAxis *angularAxis;
    QValueAxis *radialAxis;

    QList<QPointF> points;

public slots:
    void refreshChart();

protected:


private:


};

#endif // MAINWINDOW_H

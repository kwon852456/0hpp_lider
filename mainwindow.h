#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QChartView
{
public:
    MainWindow(QWidget *parent = 0);
    void refreshChart();

protected:


private:


};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

extern QPolarChart *chart;

MainWindow::MainWindow(QWidget *parent)
    : QChartView(parent)
{

}

void MainWindow::refreshChart(){

}

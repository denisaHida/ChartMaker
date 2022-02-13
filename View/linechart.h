#ifndef LINECHART_H
#define LINECHART_H
#include "chart.h"
#include "Controller/controller.h"
#include <QtCharts/QLineSeries>

class LineChart : public chart
{
    Controller* controller;
    QString title;

public:
    LineChart();
    LineChart(Controller*, QString);
    ~LineChart()=default;
    QChartView *generateView()const override;
};

#endif // LINECHART_H

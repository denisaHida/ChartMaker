#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
class BarChart : public chart
{

public:
    BarChart();
    BarChart(Controller*,QString);
    ~BarChart()=default;
    QChartView* generateView()const override;
private:
    Controller* controller;
    QString title;
};

#endif // BARCHART_H

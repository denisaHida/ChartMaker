#ifndef PIECHART_H
#define PIECHART_H
#include "chart.h"

class PieChart : public chart
{
public:
    PieChart()=default;
    PieChart(Controller*,QString);
    ~PieChart()=default;
    QChartView *generateView()const override;
private:
    Controller *controller;
    QString title;
};

#endif // PIECHART_H

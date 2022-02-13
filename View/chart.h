#ifndef CHART_H
#define CHART_H
#include "Controller/controller.h"
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE
using std::vector;
class chart
{
public:
    chart()=default;
    virtual ~chart()=default;
    virtual QChartView* generateView()const=0;
    static void generateHistogram(Controller*);
};

#endif // CHART_H

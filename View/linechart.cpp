#include "linechart.h"
#include <QDebug>

LineChart::LineChart()
{

}

LineChart::LineChart(Controller* ctr, QString t):controller(ctr), title(t)
{

}

QChartView *LineChart::generateView() const
{
     QLineSeries *series = new QLineSeries();
     for(int i=0; i< controller->getColX()->getNumRecords(); ++i)
         series->append(controller->getColX()->getRecords()[i]->getQStringValue().toDouble(),controller->getColY()->getRecords()[i]->getQStringValue().toDouble());

     QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
     chart->setTitle(title);

     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     return chartView;

}

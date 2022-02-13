#include "piechart.h"

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

PieChart::PieChart(Controller *ctr, QString t):controller(ctr), title(t)
{

}

QChartView *PieChart::generateView() const
{
    QPieSeries *serie = new QPieSeries();
    for(int i = 0; i < controller->getColX()->getNumRecords(); i++)
    {
        serie->append(controller->getColX()->getRecords()[i]->getQStringValue(),controller->getColY()->getRecords()[i]->getQStringValue().toDouble());
    }

    QChart *chart = new QChart();
    chart->addSeries(serie);
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}


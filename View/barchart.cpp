#include "barchart.h"
#include <QDebug>

BarChart::BarChart()
{

}
BarChart::BarChart(Controller* ctr, QString t):controller(ctr), title(t)
{

}

QChartView* BarChart::generateView() const
{
        vector<QBarSet*> set;

        for(int j= 0; j < controller->getColX()->getNumRecords(); j++)
        {
            set.push_back(new QBarSet(controller->getColX()->getRecords()[j]->getQStringValue()));
            set[j]->append(controller->getColY()->getRecords()[j]->getQStringValue().toDouble());
        }
        QBarSeries* serie = new QBarSeries();
        for(unsigned int i=0; i < set.size();i++)
            serie->append(set[i]);
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

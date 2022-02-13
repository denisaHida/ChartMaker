#include "chart.h"
#include <QDebug>


void chart::generateHistogram(Controller* HistogramData)
{
    HistogramData->setColX(new Column(HistogramData->getHistogramCol()->getLabel()));

    HistogramData->setColY(new Column("Frequenza"));
    
    for(int i=0; i<HistogramData->getHistogramCol()->getSize();i++)
    {
        int n = HistogramData->getColX()->found(HistogramData->getHistogramCol()->getRecords()[i]);
        if(n == -1)
        {
            HistogramData->appendRecordInX(HistogramData->getHistogramCol()->getRecords()[i]);
            HistogramData->appendRecordInY(new IntRecord(1));
        }
        else
            HistogramData->setRecordInY(n,new IntRecord(HistogramData->getColY()->getRecords()[n]->getQStringValue().toDouble() + 1));

    }
}

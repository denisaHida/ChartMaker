#include "column.h"
#include <QDebug>

Column::Column()
{

}

Column::Column(QString labelInserted):label(labelInserted),records(vector<Record*>()),typeofRecords(QString(""))
{

}

Column::Column(QString labelInserted, QString typeChosen):label(labelInserted),records(vector<Record*>()),typeofRecords(typeChosen)
{

}

Column::Column(QString labelInserted, vector<Record *> recordInserted, QString typeChosen):label(labelInserted),records(recordInserted),typeofRecords(typeChosen)
{

}

Column *Column::clone() const
{
    return new Column(*this);
}

void Column::popRecord()
{
    records.pop_back();
}

void Column::setLabel(const QString &l)
{
    label=l;
}

void Column::appendRecord(Record* rec)
{
    records.push_back(rec);
}
void Column::appendRecord(wordRecord* rec)
{
    records.push_back(rec);
}

void Column::setRecords(vector<Record *>r)
{
    records=r;
}

void Column::setRecord(int index, Record* newRec)
{
    records[index] = newRec;
}
QString Column::getLabel()
{
    return label;
}

int Column::getNumRecords() const
{
    int n=0;
    for(vector<Record*>::const_iterator i= records.begin(); i!=records.end();i++)
    {
        n++;
    }
    return n;

}

void Column::setType(const QString & t)
{
    typeofRecords = t;
}

QString Column::getType() const
{
    return typeofRecords;
}

int Column::getSize()
{
    return records.size();
}

vector<Record *> Column::getRecords() const
{
    return records;
}

int Column::found(Record * r)
{//vector<Record*>::const_iterator i= records.begin(); i!=records.end();i++
    for(unsigned int i=0; i<records.size();i++)
    {
        if(records[i]->getQStringValue() == r->getQStringValue())
            return i;
    }
    return -1;
}

void Column::clearRec()
{
    records.clear();
}


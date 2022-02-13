#include "controller.h"
#include <QDebug>
Controller::Controller():mainTable(new Table()),ChartColX(nullptr),ChartColY(nullptr), HistogramCol(nullptr), modified(false), model(nullptr)
{

}

void Controller::cloneTable(Table *table)
{
    mainTable=table->clone();
}

void Controller::addColumn(const QString &title, const QString &type)
{
    mainTable->appendColumn(new Column(title,type));
}

Table *Controller::getTable() const
{
    return mainTable;
}

void Controller::modifyTitle(const QString& t)
{
    mainTable->setTitle(t);
}

void Controller::setRows(const int & n)
{
    mainTable->setNRows(n);
}

QString Controller::getTitle() const
{
    return mainTable->getTitle();
}

void Controller::setColX(Column* x)
{
    ChartColX=x;
}

void Controller::setColY(Column* y)
{
    ChartColY=y;
}

Column* Controller::getColX()const
{
    return ChartColX;
}

Column* Controller::getColY()const
{
    return ChartColY;
}

void Controller::setHistogramCol(Column* Hc)
{
    HistogramCol=Hc;
}

Column* Controller::getHistogramCol()const
{
    return HistogramCol;
}

void Controller::appendRecord(int cIndex, Record * newRec)
{
    mainTable->appendRecord(cIndex,newRec);
}

void Controller::appendRecordInX(Record* rec)
{
    ChartColX->appendRecord(rec);
}

void Controller::appendRecordInY(Record* rec)
{
    ChartColY->appendRecord(rec);
}

void Controller::setRecordInX(int n, Record* rec)
{
    ChartColX->setRecord(n,rec);
}   

void Controller::setRecordInY(int n, Record* rec)
{
    ChartColY->setRecord(n,rec);
}

void Controller::setTable(Table *t)
{
    mainTable=t;
}

void Controller::clearRecords()
{
    mainTable->clearRecords();
}

void Controller::setTableNRows(int n)
{
    mainTable->setNRows(n);
}

void Controller::popRow()
{
    mainTable->popRow();
}

void Controller::clear()
{
    delete mainTable;
    delete ChartColX;
    delete ChartColY;
    delete HistogramCol;
    delete model;
    mainTable=new Table();
    ChartColX = nullptr;
    ChartColY = nullptr;
    HistogramCol = nullptr;
    modified=false;
}

bool Controller::gotModified() const
{
    return modified;
}

void Controller::setModified(bool b)
{
    modified=b;
}

bool Controller::isEmpty() const
{
    return mainTable->getNumCol()==0;
}

void Controller::setModel(Model *m)
{
    model=m;
}

Model *Controller::getModel() const
{
    return model;
}

Table *Controller::loadModel(const QString &s) const
{
    return model->load(s);
}

void Controller::removeCol()
{
    qDebug()<<"in controller2";
    mainTable->removeCol();
    if(model)
    model->setMainTable(mainTable);
    qDebug()<<"in controller";
}

void Controller::saveInModel(QFile & f)
{
    model->save(f);
}

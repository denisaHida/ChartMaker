#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/table.h"
#include "Model/model.h"
class Controller
{
public:
    Controller();
    void cloneTable(Table *);
    void addColumn(const QString&,const QString&);
    Table* getTable()const;
    void modifyTitle(const QString&);
    void setRows(const int&);
    QString getTitle()const;
    void setColX(Column*);
    void setColY(Column*);
    Column* getColX()const;
    Column* getColY()const;
    void setHistogramCol(Column*);
    Column* getHistogramCol()const;
    void appendRecord(int,Record*);
    void appendRecordInX(Record*);
    void appendRecordInY(Record*);
    void setRecordInX(int, Record*);
    void setRecordInY(int, Record*);
    void setTable(Table*);
    void clearRecords();
    void setTableNRows(int);
    void popRow();
    void clear();
    bool gotModified()const;
    void setModified(bool);
    bool isEmpty()const;
    void setModel(Model*);
    Model* getModel()const;
    void saveInModel(QFile&);
    Table* loadModel(const QString&)const;
    void removeCol();
private:
    Table* mainTable;
    Column* ChartColX;
    Column* ChartColY;
    Column* HistogramCol;
    bool modified;
    Model* model;
};

#endif // CONTROLLER_H

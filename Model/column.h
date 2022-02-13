#ifndef COLUMN_H
#define COLUMN_H
#include <string>
#include <QString>
#include <vector>
#include "record.h"
#include "intrecord.h"
#include "doublerecord.h"
#include "wordrecord.h"

using std::string;
using std::vector;
class Column
{
private:
    QString label;
    vector<Record*> records;
    QString typeofRecords;
public:
    Column();
    Column(QString labelInserted);
    Column(QString labelInserted, QString typeChosen);
    Column(QString labelInserted, vector<Record*> recordInserted, QString typeChosen);
    ~Column()=default;
    Column *clone() const;
    void appendRecord(Record*);
    void appendRecord(wordRecord*);
    void setRecords(vector<Record*>);
    void setRecord(int,Record*);
    void popRecord();
    void setLabel(const QString&);
    QString getLabel();
    int getNumRecords()const;
    void setType(const QString&);
    QString getType() const;
    int getSize();
    vector<Record*> getRecords()const;
    int found(Record*);
    void clearRec();

};

#endif // COLUMN_H

#ifndef TABLE_H
#define TABLE_H
#include "record.h"
#include "column.h"
#include <QString>
class Table
{
    QString title;
    vector<Column*> columns;
    int nRows;
public:
    Table()=default;
    Table(QString titolo, vector<Column*> colInserted);
    Table(vector<Column*> colInserted);
    ~Table()=default;
    Table *clone() const;
    void appendRow(const vector<Record*>& );
    void appendColumn(Column*);
    void popRow();
    void setTitle(const QString&);
    QString getTitle() const;
    void setColumns(vector<Column*> col);
    vector<Column *> getColumns() const;
    int getNumCol()const;
    int getNumRows() const;
    void setNRows(int nRow);
    void clearRecords();
    void appendRecord(int,Record*);
    void removeCol();
};

#endif // TABLE_H

#include "table.h"
#include <QDebug>

Table::Table(QString titolo, vector<Column *> colInserted):title(titolo), columns(colInserted)
{

}

Table::Table(vector<Column *> colInserted):columns(colInserted)
{

}

Table *Table::clone() const
{
    return new Table(*this);
}

void Table::appendRow(const vector<Record *> & r)
{

    vector<Record*>::const_iterator iR = r.begin();
    for(vector<Column*>::iterator i= columns.begin(); i!=columns.end() && iR!=r.end();i++)
    {
       (*i)->appendRecord((*iR));
       iR++;
    }

}

void Table::appendColumn(Column* col)
{
    columns.push_back(col);
}

void Table::popRow()
{
    for(unsigned int i=0; i<columns.size(); i++)
    {
        columns[i]->popRecord();
    }
    --nRows;
}

void Table::setTitle(const QString & t)
{
    title=t;
}

QString Table::getTitle() const
{
    return title;
}

void Table::setColumns(vector<Column *> col)
{
    columns=col;
}

vector<Column *> Table::getColumns() const
{
    return columns;
}

int Table::getNumCol() const
{
    int n=0;
    for(vector<Column*>::const_iterator i = columns.begin();i != columns.end();i++)
    {
        n++;
    }

    return n;
}

int Table::getNumRows() const
{

        return nRows;
}

void Table::setNRows(int nRow)
{
    nRows=nRow;
}

void Table::clearRecords()
{
    for(unsigned int i=0; i< columns.size();++i)
        columns[i]->clearRec();
}

void Table::appendRecord(int cIndex, Record * newRec)
{
    columns[cIndex]->appendRecord(newRec);
}

void Table::removeCol()
{
    columns.pop_back();

}

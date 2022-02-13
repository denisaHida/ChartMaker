#ifndef MODEL_H
#define MODEL_H
#include <QFile>
#include "table.h"
class Model
{
private:
    Table* mainTable;

public:
    Model(Table*);
    void setMainTable(Table*);
    void save(QFile &file);
    Table* load(QString);
};

#endif // MODEL_H

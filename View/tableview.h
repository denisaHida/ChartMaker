#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <vector>
#include "Controller/controller.h"
using std::vector;
class TableView : public QTableWidget
{
      Q_OBJECT
private:
    Controller* controller;
    vector<QWidget*> elementsList;
public:
    TableView()=default;
    TableView(QWidget *parent=0,Controller *c=0);
    void insertData();
    vector<QWidget*> getElementList()const;
    void addRow();
    void removeRow();
    void removeCol();
};

#endif // TABLEVIEW_H

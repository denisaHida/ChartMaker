#ifndef TABVIEW_H
#define TABVIEW_H

#include <QTabWidget>
#include "View/tableview.h"
#include "Controller/controller.h"

class TabView : public QTabWidget
{
    Q_OBJECT
private:
    TableView* tableViewWid;
    Controller* controller;
public:
    TabView(QWidget* parent, Controller* mC);
    TableView* getTableWid()const;
    void removeCol();
public slots:
    void addRow();
    void removeRow();
};

#endif // TABVIEW_H

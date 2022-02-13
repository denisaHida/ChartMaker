#include "View/tabview.h"
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE


TabView::TabView(QWidget *parent, Controller * mC): QTabWidget(parent), controller(mC)
{
    setTabShape(QTabWidget::Triangular);
    setTabsClosable(true);
    qDebug() << "tabview start";
    tableViewWid = new TableView(this,controller);
    addTab(tableViewWid,"Data");
    setCurrentWidget(tableViewWid);
}

TableView *TabView::getTableWid() const
{
    return tableViewWid;
}

void TabView::removeCol()
{
    tableViewWid->removeCol();
    controller->setModified(true);
    setCurrentWidget(tableViewWid);
}

void TabView::addRow()
{
    tableViewWid->addRow();
    controller->setModified(true);
    setCurrentWidget(tableViewWid);
}

void TabView::removeRow()
{
    tableViewWid->removeRow();
    controller->setModified(true);
    setCurrentWidget(tableViewWid);
}

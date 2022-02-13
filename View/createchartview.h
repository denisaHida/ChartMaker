#ifndef CREATECHARTVIEW_H
#define CREATECHARTVIEW_H
#include<QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QtCharts/QChartView>
#include "Controller/controller.h"
QT_CHARTS_USE_NAMESPACE
class CreateChartView : public QDialog
{
    Q_OBJECT

public:
    CreateChartView(QWidget* parent=0,Controller*mT=0);
    QChartView* getChartView();
    QString getTitle()const;

public slots:
    void accept();
private:
    Controller* controller;
    QString XCol;
    QString YCol;
    QString title;
    int ColumnChosenHistogram;
    vector<int> ids;
    
    //QWidgets
    QLineEdit* titoloWid;
    QCheckBox* isHistogramCheck;
    QRadioButton* linechart,* piechart, *barchart;
    QVBoxLayout* container1;
    QDialog* input;
    QChartView* chartView;
    QComboBox* columnSelect;
    QComboBox* columnXSelect;
    QComboBox* columnYSelect;
    
    //funzioni
    void histogramChoseColumn();
    bool lineChosed();
    bool pieOrBarChosed();
};

#endif // CREATECHARTVIEW_H

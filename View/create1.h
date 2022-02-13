#ifndef NEWWINDOW_H
#define NEWWINDOW_H
#include "Controller/controller.h"
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <string>
#include <QVBoxLayout>
#include <vector>
using std::string;
class Create1 : public QDialog
{
    Q_OBJECT
    public:
        Create1(QWidget *parent =0, Controller* ctr=0, bool n=true);
        QFormLayout *formLayout;
        QLineEdit *titoloWid;
        QSpinBox *nColWid;
        QSpinBox *nRowWid;
        QVBoxLayout *container1;
        Table *mainTable;
    private:
        QPushButton *ok;
        Controller* controller;
        bool NewFile;
    signals:
        void New();

    private slots:
        void accept();

};
#endif

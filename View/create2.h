#ifndef CREATE2_H
#define CREATE2_H
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include<vector>
#include "Controller/controller.h"
using std::vector;
class Create2 : public QDialog
{
    Q_OBJECT
private:
    Controller* controller;
    int nCol;
    QComboBox* type;
    vector<QLineEdit*> ColNames;
    vector<QString> ColTypes;
    vector<QComboBox*> ColTypesWids;
public:
    Create2(QDialog* parent = nullptr,Controller* ctr=nullptr, int c = 0);

signals:
    void NewCreate2();
private slots:
    void accept();
};

#endif // CREATE2_H

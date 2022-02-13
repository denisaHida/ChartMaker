#include "create2.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
#include <QDebug>


Create2::Create2(QDialog *parent, Controller* ctr, int nC) :QDialog(parent), controller(ctr), nCol(nC)
{
    setWindowTitle(controller->getTitle());
    resize(500,300);
    setModal(true);

    QLineEdit* NewField;
    QLabel* label1;
    QLabel* label2;
    QHBoxLayout* ColRow;
    QVBoxLayout* ColTable= new QVBoxLayout();
    ColTable->addWidget(new QLabel("Inserisci il nome e il tipo di ogni colonna:"));
    for(int i =1; i<=nCol; i++)
    {
        ColRow= new QHBoxLayout();
        NewField =new QLineEdit();
        label1=new QLabel("Column Name: ");
        label2=new QLabel("Column type: ");

        ColRow->addWidget(label1);
        ColRow->addWidget(NewField);
        ColRow->addWidget(label2);
        ColNames.push_back(NewField);
        type = new QComboBox();
        type->addItem("intero");
        type->addItem("decimale");
        type->addItem("lettere");
        ColRow->addWidget(type);
        ColTypesWids.push_back(type);
        ColTable->addLayout(ColRow);
    }
    QPushButton* ok =new QPushButton(tr("Avanti"));
    ok->setFont(QFont("Arial",18,QFont::Black));
    QPushButton* cancel =new QPushButton(tr("Anulla"));
    cancel->setFont(QFont("Arial",18,QFont::Black));

    QDialogButtonBox* button=new QDialogButtonBox(Qt::Horizontal);
    button->addButton(ok,QDialogButtonBox::ActionRole);
    button->addButton(cancel,QDialogButtonBox::ActionRole);
    ColTable->addWidget(button);

    connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

    setLayout(ColTable);
}


void Create2::accept()
{
    for(unsigned int i=0; i<ColTypesWids.size();++i)
    {
        ColTypes.push_back(ColTypesWids[i]->currentText());
    }

    for(unsigned int i=0; i< ColNames.size();i++)
    {
        controller->addColumn(ColNames[i]->text(),ColTypes[i]);
    }


    QDialog::accept();

}

#include "create1.h"
#include "create2.h"
#include <QDebug>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>


Create1::Create1(QWidget *parent, Controller* ctr, bool n) :QDialog(parent), controller(ctr), NewFile(n)
{
    setModal(true);
    formLayout = new QFormLayout();

    if(NewFile)
    {
        setWindowTitle("Crea un nuovo dataset");
        resize(700,400);
        titoloWid = new QLineEdit();
        formLayout->addRow(tr("&Titolo"),titoloWid);
    }
    else
    {
        setWindowTitle("Aggiungi Colonne");
        resize(400,200);
    }

    nColWid=new QSpinBox();
    nColWid->setRange(0,99);
    nColWid->setValue(0);
    nColWid->setAccelerated(true);

    formLayout->addRow(tr("&Inserisci il numero di colonne:"),nColWid);

    if(NewFile)
    {
        nRowWid = new QSpinBox();
        nRowWid->setRange(0,99);
        nRowWid->setValue(0);
        nRowWid->setAccelerated(true);

        formLayout->addRow(tr("&Inserisci il numero di rige:"),nRowWid);
    }


    container1=new QVBoxLayout();
    container1->addLayout(formLayout);
    ok =new QPushButton(tr("Next"));
    QPushButton *annulla=new QPushButton("Annulla");

    ok->setFont(QFont("Arial",18,QFont::Black));
    annulla->setFont(QFont("Arial",18,QFont::Black));

    connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(annulla, SIGNAL(clicked()),this, SLOT(close()));
    QDialogButtonBox *button=new QDialogButtonBox(Qt::Horizontal);
    button->addButton(ok,QDialogButtonBox::ActionRole);
    button->addButton(annulla,QDialogButtonBox::ActionRole);
    container1->addWidget(button);
    setLayout(container1);

}

void Create1::accept()
{
    if(NewFile)
    {
        if(titoloWid->text().isEmpty() || !nColWid->value()){
            QMessageBox messageBoxLez;
            messageBoxLez.critical(0,"Error","Errore: Non hai inserito il campo titolo o il numero delle colonne!");
            messageBoxLez.setFixedSize(500,200);
        }
        else
        {
            controller->modifyTitle(titoloWid->text());
            controller->setRows(nRowWid->value());
            Create2 *crea=new Create2(this, controller, nColWid->value());
            if(crea->exec())
            {
                QDialog::accept();
            }
            else
                close();
        }
    }
    else
    {
        Create2 *crea = new Create2(this, controller, nColWid->value());
        if(crea->exec())
        {
            QDialog::accept();
        }
        else
            close();
    }
}


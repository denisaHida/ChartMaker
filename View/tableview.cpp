#include "tableview.h"
#include <QStringList>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDebug>

TableView::TableView(QWidget *parent, Controller *c): QTableWidget(parent), controller(c)
{

    setColumnCount(controller->getTable()->getNumCol());
    QStringList titles;
    vector<Column*> temp = controller->getTable()->getColumns();
    for(auto i = temp.begin(); i!=temp.end();i++)
    {
      titles<<(*i)->getLabel();
    }

    setHorizontalHeaderLabels(titles);
    setRowCount(controller->getTable()->getNumRows());

    for(int i=0; i<controller->getTable()->getNumRows(); i++)
    {
        for(int j=0; j < controller->getTable()->getNumCol(); j++)
        {
            QWidget *element;
            if(controller->getTable()->getColumns()[j]->getType() == "decimale")
            {
                element=new QDoubleSpinBox();
                if(controller->getTable()->getColumns()[j]->getRecords().size() != 0)
                {
                    double vall = dynamic_cast<DoubleRecord*>(controller->getTable()->getColumns()[j]->getRecords()[i])->getValue();
                    dynamic_cast<QDoubleSpinBox*>(element)->setValue(vall);
                }
            }
            else if(controller->getTable()->getColumns()[j]->getType() == "intero")
            {
                element=new QSpinBox();
                if(controller->getTable()->getColumns()[j]->getRecords().size() != 0)
                {
                    int val = dynamic_cast<IntRecord*>(controller->getTable()->getColumns()[j]->getRecords()[i])->getValue();
                    dynamic_cast<QSpinBox*>(element)->setValue(val);
                }
            }
            else
            {
                element=new QLineEdit();
                if(controller->getTable()->getColumns()[j]->getRecords().size() != 0)
                {
                    dynamic_cast<QLineEdit*>(element)->setText(controller->getTable()->getColumns()[j]->getRecords()[i]->getQStringValue());
                }
            }
            setCellWidget(i,j,element);
            elementsList.push_back(element);
        }
    }
}


vector<QWidget *> TableView::getElementList() const
{
    return elementsList;
}

void TableView::addRow()
{
    int nR = controller->getTable()->getNumRows();

    setRowCount(nR+1);
    controller->setTableNRows(nR+1);

    for(int j=0; j < controller->getTable()->getNumCol(); j++)
    {
        QWidget* element;
        if(controller->getTable()->getColumns()[j]->getType() == "decimale")
        {
            element=new QDoubleSpinBox();
        }
        else if(controller->getTable()->getColumns()[j]->getType() == "intero")
        {
            element=new QSpinBox();
        }
        else
            element=new QLineEdit();
        setCellWidget(nR,j,element);
        elementsList.push_back(element);
    }

}

void TableView::removeRow()
{
    int nR = controller->getTable()->getNumRows();

    if(nR > 0)
    {
        int nC = controller->getTable()->getNumCol();
        for(int j=0; j < nC; j++)
        {
            removeCellWidget(nR-1,j);
            elementsList.pop_back();
        }
        setRowCount(nR-1);
        controller->popRow();
    }

}

void TableView::removeCol()
{
    int nC = controller->getTable()->getNumCol();
    vector<QWidget*> temp;
    if(nC > 0)
    {
        int nR = controller->getTable()->getNumRows();
        qDebug()<<"elementlist size "<<elementsList.size();
        qDebug()<<"size "<<nR*nC;

        for(int j=0; j < nR*nC; j++)
        {
            if((j+1)%nC!=0)
                temp.push_back(elementsList[j]);

            removeCellWidget((j+1)/nC-1,nC-1);

        }

        setColumnCount(nC-1);
        elementsList=temp;
        qDebug()<<"before calling romove col";
        controller->removeCol();
    }

}



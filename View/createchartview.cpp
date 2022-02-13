#include "createchartview.h"
#include "linechart.h"
#include "barchart.h"
#include "piechart.h"
#include <QDialogButtonBox>
#include <QDebug>
#include <QSize>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QInputDialog>


CreateChartView::CreateChartView(QWidget* parent,Controller* T):QDialog(parent), controller(T)
{
    qDebug()<<"Start of createchartview";
    setWindowTitle("Crea un chart");
    resize(700,500);
    setModal(true);

    QFormLayout* formLayout = new QFormLayout();

    QLabel* titolo= new QLabel("Titolo");
    titoloWid = new QLineEdit();

    formLayout->addRow(titolo,titoloWid);

    QLabel* HistogramLabel = new QLabel("Histogram");
    isHistogramCheck=new QCheckBox();
    HistogramLabel->setFont(QFont("Arial",16,QFont::Black));

    formLayout->addRow(HistogramLabel,isHistogramCheck);

    container1=new QVBoxLayout();
    container1->addLayout(formLayout);

    QGroupBox* chartGroup=new QGroupBox(tr("Charts"));
    QLabel* chartsLabel=new QLabel();

    linechart=new QRadioButton();
    linechart->setIcon(QIcon(":/Images/Images/lineChart.png"));
    linechart->setIconSize(QSize(100,100));

    piechart=new QRadioButton();
    piechart->setIcon(QIcon(":/Images/Images/pieChart.png"));
    piechart->setIconSize(QSize(100,100));

    barchart=new QRadioButton();
    barchart->setIcon(QIcon(":/Images/Images/barChart.png"));
    barchart->setIconSize(QSize(100,100));

    barchart->setCheckable(true);
    linechart->setCheckable(true);
    piechart->setCheckable(true);
    barchart->setChecked(true);
    linechart->setChecked(false);
    piechart->setChecked(false);
    QVBoxLayout* buttongrafico=new QVBoxLayout();
    buttongrafico->addWidget(chartsLabel);
    buttongrafico->addWidget(linechart);
    buttongrafico->addWidget(piechart);
    buttongrafico->addWidget(barchart);
    chartGroup->setLayout(buttongrafico);
    formLayout->addWidget(chartGroup);

    QPushButton* next=new QPushButton("Next");
    next->setFont(QFont("Arial",18,QFont::Black));
    QPushButton* annulla=new QPushButton("Annulla");
    annulla->setFont(QFont("Arial",18,QFont::Black));


    QDialogButtonBox* button=new QDialogButtonBox(Qt::Horizontal);
    button->addButton(next,QDialogButtonBox::ActionRole);
    button->addButton(annulla,QDialogButtonBox::ActionRole);

    connect(next, SIGNAL(clicked()),this, SLOT(accept()));
    connect(annulla, SIGNAL(clicked()),this, SLOT(close()));


    container1->addWidget(button);
    setLayout(container1);



}

QChartView *CreateChartView::getChartView()
{
    return chartView;
}

QString CreateChartView::getTitle() const
{
    return title;
}

bool CreateChartView::lineChosed()
{

    this->setVisible(false);
    input=new QDialog();
    input->resize(400,200);

    QFormLayout* container2;


    if(isHistogramCheck->isChecked())
    {
        input->setWindowTitle("Seleziona la colonna che si vuole rappresentare");

        columnSelect = new QComboBox();
        container2 = new QFormLayout();

        QLabel* colLabel = new QLabel("Seleziona la Colonna:");
        QStringList items;
        int nC=controller->getTable()->getNumCol();
        for(int i=0; i<nC; i++)
        {
            items << controller->getTable()->getColumns()[i]->getLabel();
        }
        columnSelect->addItems(items);
        container2->addRow(colLabel,columnSelect);
    }
    else
    {
        input->setWindowTitle("Seleziona le colonna che si vuole rappresentare");

        columnXSelect = new QComboBox();
        columnYSelect = new QComboBox();
        container2 = new QFormLayout();
        QLabel* colXLabel = new QLabel("Seleziona la Colonna per l'asse X:");
        QLabel* colYLabel = new QLabel("Seleziona la Colonna per l'asse Y:");
        int nC=controller->getTable()->getNumCol();
        QStringList items;
        ids.clear();
        for(int i=0; i<nC; i++)
        {
            if(controller->getTable()->getColumns()[i]->getType() != "lettere")
            {
                ids.push_back(i);
                items << controller->getTable()->getColumns()[i]->getLabel();
            }
        }
        columnXSelect->addItems(items);
        columnYSelect->addItems(items);
        container2->addRow(colXLabel,columnXSelect);
        container2->addRow(colYLabel,columnYSelect);
     }

    QPushButton* next=new QPushButton("Next");
    next->setFont(QFont("Arial",14,QFont::Black));

    QPushButton* annulla=new QPushButton("Annulla");
    annulla->setFont(QFont("Arial",14,QFont::Black));

    QDialogButtonBox* button=new QDialogButtonBox(Qt::Horizontal);
    button->addButton(next,QDialogButtonBox::ActionRole);
    button->addButton(annulla,QDialogButtonBox::ActionRole);

    container2->addWidget(button);
    input->setLayout(container2);

    connect(next, SIGNAL(clicked()),input, SLOT(accept()));
    connect(annulla, SIGNAL(clicked()),input, SLOT(close()));

    if(input->exec())
    {
        LineChart* lC;
        if(isHistogramCheck->isChecked())
        {
            controller->setHistogramCol(controller->getTable()->getColumns()[columnSelect->currentIndex()]);
            chart::generateHistogram(controller);
            lC = new LineChart(controller,titoloWid->text());
        }
        else
        {
            controller->setColX(controller->getTable()->getColumns()[ids[columnXSelect->currentIndex()]]);
            controller->setColY(controller->getTable()->getColumns()[ids[columnYSelect->currentIndex()]]);
            lC = new LineChart(controller,titoloWid->text());
        }
        chartView = lC->generateView();
        if(titoloWid->text().isEmpty())
        {
            title="Line Chart";
        }
        else
        title = titoloWid->text();
        return true;
    }
    else
    {
        this->setVisible(true);
        return false;
    }
}

bool CreateChartView::pieOrBarChosed()
{
    qDebug()<<"Start of pieorbar..........";
    this->setVisible(false);
    input=new QDialog();
    input->resize(400,200);

    QFormLayout* container2;


    if(isHistogramCheck->isChecked())
    {
        input->setWindowTitle("Seleziona la colonna che si vuole rappresentare");

        columnSelect = new QComboBox();
        container2 = new QFormLayout();

        QLabel* colLabel = new QLabel("Seleziona la Colonna:");
        QStringList items;
        int nC=controller->getTable()->getNumCol();
        for(int i=0; i<nC; i++)
        {
            items << controller->getTable()->getColumns()[i]->getLabel();
        }
        columnSelect->addItems(items);
        container2->addRow(colLabel,columnSelect);
    }
    else
    {
        input->setWindowTitle("Seleziona le colonna che si vuole rappresentare");

        columnXSelect = new QComboBox();
        columnYSelect = new QComboBox();
        container2 = new QFormLayout();
        QLabel* colXLabel = new QLabel("Seleziona la Colonna per l'asse X:");
        QLabel* colYLabel = new QLabel("Seleziona la Colonna per l'asse Y:");
        int nC=controller->getTable()->getNumCol();
        QStringList items;
        QStringList itemsAll;
        ids.clear();
        for(int i=0; i<nC; i++)
        {
            if(controller->getTable()->getColumns()[i]->getType() != "lettere")
            {
                ids.push_back(i);
                items << controller->getTable()->getColumns()[i]->getLabel();
            }
            itemsAll << controller->getTable()->getColumns()[i]->getLabel();
         }
        columnXSelect->addItems(itemsAll);
        columnYSelect->addItems(items);
        container2->addRow(colXLabel,columnXSelect);
        container2->addRow(colYLabel,columnYSelect);

    }
    QPushButton* next=new QPushButton("Next");
    next->setFont(QFont("Arial",14,QFont::Black));

    QPushButton* annulla=new QPushButton("Annulla");
    annulla->setFont(QFont("Arial",14,QFont::Black));

    QDialogButtonBox* button=new QDialogButtonBox(Qt::Horizontal);
    button->addButton(next,QDialogButtonBox::ActionRole);
    button->addButton(annulla,QDialogButtonBox::ActionRole);

    container2->addWidget(button);
    input->setLayout(container2);

    connect(next, SIGNAL(clicked()),input, SLOT(accept()));
    connect(annulla, SIGNAL(clicked()),input, SLOT(close()));

    if(input->exec())
    {
        if(barchart->isChecked())
        {
            BarChart* bC;
            if(isHistogramCheck->isChecked())
            {
                controller->setHistogramCol(controller->getTable()->getColumns()[columnSelect->currentIndex()]);
                chart::generateHistogram(controller);
                bC = new BarChart(controller,titoloWid->text());
            }
            else
            {
                controller->setColX(controller->getTable()->getColumns()[columnXSelect->currentIndex()]);
                controller->setColY(controller->getTable()->getColumns()[ids[columnYSelect->currentIndex()]]);
                bC = new BarChart(controller,titoloWid->text());
            }
            chartView = bC->generateView();
            if(titoloWid->text().isEmpty())
            {
                title="Bar Chart";
            }
            else
            title = titoloWid->text();
        }
        else
        {
            PieChart* pC;
            if(isHistogramCheck->isChecked())
            {
                controller->setHistogramCol(controller->getTable()->getColumns()[columnSelect->currentIndex()]);
                chart::generateHistogram(controller);
                pC = new PieChart(controller,titoloWid->text());
            }
            else
            {
                controller->setColX(controller->getTable()->getColumns()[columnXSelect->currentIndex()]);
                controller->setColY(controller->getTable()->getColumns()[ids[columnYSelect->currentIndex()]]);
                pC = new PieChart(controller,titoloWid->text());
            }
            chartView = pC->generateView();
            if(titoloWid->text().isEmpty())
            {
                title="Pie Chart";
            }
            else
            title = titoloWid->text();
        }
        return true;
    }
    else
    {
        this->setVisible(true);
        return false;
    }
}


void CreateChartView::accept()
{
    bool accepted=false;
    if(linechart->isChecked())
        accepted = lineChosed();
    else if(barchart->isChecked() || piechart->isChecked())
        accepted = pieOrBarChosed();
    if(accepted)
        QDialog::accept();
}

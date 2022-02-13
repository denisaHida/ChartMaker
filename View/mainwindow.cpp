#include "createchartview.h"
#include "View/tabview.h"
#include "mainwindow.h"
#include "create2.h"
#include "barchart.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QStatusBar>
#include <QMessageBox>
#include <string>
#include <QTextEdit>
#include <QDebug>
using std::string;


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), controller(new Controller()), tabsNum(0)
{
    setGeometry(200,100,900,600);
    setWindowTitle(tr("ChartMaker"));

    OpenAction=new QAction(QIcon(":/Images/Images/openFile.png"),tr("Apri"),this);
    OpenAction->setShortcuts(QKeySequence::Open);
    NewAction=new QAction(QIcon(":/Images/Images/new-document.png"),tr("Nuovo"),this);
    NewAction->setShortcuts(QKeySequence::New);
    SaveAction=new QAction(QIcon(":/Images/Images/saveFile.png"),tr("Salva"),this);
    SaveAction->setShortcuts(QKeySequence::Save);
    SaveAction->setEnabled(false);
    SaveAsAction=new QAction(QIcon(":/Images/Images/saveFile.png"),tr("Salva come"),this);
    SaveAsAction->setShortcuts(QKeySequence::SaveAs);
    SaveAsAction->setEnabled(false);
    QuitAction=new QAction(QIcon(":/Images/Images/close.png"),tr("Esci"),this);
    QuitAction->setShortcuts(QKeySequence::Quit);
    ChartAction=new QAction(QIcon(":/Images/Images/chart.png"),tr("Chart"),this);
    ChartAction->setEnabled(false);
    AddRowAction=new QAction(QIcon(":/Images/Images/addRow.png"),tr("Aggiungi Riga"),this);
    AddRowAction->setEnabled(false);
    RemoveRowAction=new QAction(QIcon(":/Images/Images/deleteRow.png"),tr("Rimouvi Riga"),this);
    RemoveRowAction->setEnabled(false);
    AddColAction=new QAction(QIcon(":/Images/Images/addCol.png"),tr("Aggiungi Colonne"),this);
    AddColAction->setEnabled(false);
    RemoveColAction=new QAction(QIcon(":/Images/Images/deleteCol.png"),tr("Rimouvi Colonne"),this);
    RemoveColAction->setEnabled(false);
    SaveModAction=new QAction(QIcon(":/Images/Images/tick.png"),tr("Salva Modifiche"),this);
    SaveModAction->setEnabled(false);
    CloseAction=new QAction(QIcon(":/Images/Images/close2.png"),tr("Chiudi"),this);
    CloseAction->setEnabled(false);

    FileMenu = new QMenu(tr("File"),this);
    FileMenu->addAction(OpenAction);
    FileMenu->addAction(NewAction);
    FileMenu->addAction(SaveAction);
    FileMenu->addAction(SaveAsAction);
    FileMenu->addAction(ChartAction);
    FileMenu->addSeparator();
    FileMenu->addAction(QuitAction);

    menuBar()->addMenu(FileMenu);
    menuBar()->addSeparator();


    File=addToolBar(tr("File"));
    File->addAction(OpenAction);
    File->addAction(NewAction);
    File->addAction(SaveAction);
    File->addSeparator();
    File->addAction(ChartAction);
    File->setIconSize(QSize(30,30));


    QToolBar* modifyLayout=new QToolBar("Modifica");
    modifyLayout->addAction(AddRowAction);
    modifyLayout->addAction(RemoveRowAction);
    modifyLayout->addAction(AddColAction);
    modifyLayout->addAction(RemoveColAction);
    modifyLayout->addSeparator();
    modifyLayout->addAction(SaveModAction);
    modifyLayout->addAction(CloseAction);
    modifyLayout->setOrientation(Qt::Vertical);
    modifyLayout->setIconSize(QSize(40,50));
    addToolBar(Qt::LeftToolBarArea,modifyLayout);

    connect(NewAction,SIGNAL(triggered()),this,SLOT(NewFile()));
    connect(OpenAction,SIGNAL(triggered()),this,SLOT(OpenFile()));
    connect(ChartAction,SIGNAL(triggered()),this,SLOT(OpenChart()));
    connect(SaveAction,SIGNAL(triggered()),this,SLOT(Save()));
    connect(SaveAsAction,SIGNAL(triggered()),this,SLOT(SaveAs()));
    connect(QuitAction,SIGNAL(triggered()),this,SLOT(Close()));


}

void MainWindow::NewFile()
{
    if(!controller->isEmpty())
        Close();
    qDebug()<<"in newfile";
    Create1* crea=new Create1(this,controller,true);
    if(crea->exec())
    {
        qDebug()<<controller->getTitle();
        showDataTable();
        controller->setModified(true);
        SaveAction->setEnabled(true);
    }
}


void MainWindow::SaveAs()
{
    qDebug()<<"in saveas start";
    try
    {
        if(!controller->isEmpty())
        {
            saveRecords();
            tabs->setCurrentIndex(0);
            QString filename = QFileDialog::getSaveFileName(this,tr("Salva come"),QDir::currentPath(),"*.xml");
            if(!filename.isEmpty())
            {

                qDebug()<<"in saveas before model";
                controller->setModel(new Model(controller->getTable()));
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly))
                {
                    controller->saveInModel(file);
                    file.close();
                    OpenedFile=filename;
                }
                 else
                {
                    file.close();
                    throw QString("Il file è apperto in modalità ReadOnly!");
                }
            }
            else throw QString("Nessun dato da salvare!");
        }
    }catch(QString s)
    {
        QMessageBox::warning(0,"Attenzione!",s);
    }
}

void MainWindow::Save()
{
    if(OpenedFile.isEmpty())
    {
        qDebug()<<"before the saveas call";
        SaveAs();
    }
    else
    {
        saveRecords();
        tabs->setCurrentIndex(0);
        controller->setModel(new Model(controller->getTable()));
        QFile file(OpenedFile);
        if (file.open(QIODevice::WriteOnly))
        {
            controller->saveInModel(file);
            file.close();

        }
         else
        {
            file.close();

        }

    }
}
void MainWindow::CloseFile()
{
    try
    {
        qDebug()<<"close file";
        if(!controller->isEmpty())
        {
            delete tabs;
            qDebug()<<"close file1";
            controller->clear();
            qDebug()<<"close file2";
            OpenedFile="";
        }
        else
            throw 0;
    }
    catch(int)
    {
            QMessageBox::warning(0,"Attenzione!","Non ci sono dati da chiudere!");
    }
}
void MainWindow::closeTab(int i)
{
    qDebug()<<tabs->tabText(i);
    if(tabs->tabText(i)=="Data")
    {
        Close();
    }
    else
        tabs->removeTab(i);
}

void MainWindow::addCol()
{
    saveRecords();
    Create1* crea=new Create1(this,controller,false);
    if(crea->exec())
    {
        qDebug()<<controller->getTable()->getNumCol()<<"    after create";
        showDataTable();
    }
}

void MainWindow::removeCol()
{
    tabs->removeCol();
}

void MainWindow::showDataTable()
{
    qDebug()<<"before table show function";
    tabs = new TabView(this,controller);
    setCentralWidget(tabs);
    qDebug()<<"after seting central widget";
    AddRowAction->setEnabled(true);
    RemoveRowAction->setEnabled(true);
    AddColAction->setEnabled(true);
    RemoveColAction->setEnabled(true);
    ChartAction->setEnabled(true);
    SaveAction->setEnabled(true);
    SaveAsAction->setEnabled(true);
    SaveModAction->setEnabled(true);
    CloseAction->setEnabled(true);

    connect(AddRowAction,SIGNAL(triggered()),tabs,SLOT(addRow()));
    connect(RemoveRowAction,SIGNAL(triggered()),tabs,SLOT(removeRow()));
    connect(AddColAction,SIGNAL(triggered()),this,SLOT(addCol()));
    connect(RemoveColAction,SIGNAL(triggered()),this,SLOT(removeCol()));
    connect(SaveModAction,SIGNAL(triggered()),this,SLOT(Save()));
    connect(CloseAction,SIGNAL(triggered()),this,SLOT(Close()));

}
void MainWindow::saveRecords()
{
 vector<QWidget *> elementList = tabs->getTableWid()->getElementList();

 int index = 0;
 controller->clearRecords();
 controller->setModified(true);
 for(int i=0; i < controller->getTable()->getNumRows(); ++i)
 {

         for(int cIndex=0; cIndex < controller->getTable()->getNumCol(); ++cIndex)
         {
             if(dynamic_cast<QDoubleSpinBox*>(elementList[cIndex]))
             {
                 double val = dynamic_cast<QDoubleSpinBox*>(elementList[index])->value();
                 controller->appendRecord(cIndex,new DoubleRecord(val));
             }
             else if(dynamic_cast<QSpinBox*>(elementList[cIndex]))
             {
                 int val = dynamic_cast<QSpinBox*>(elementList[index])->value();
                 controller->appendRecord(cIndex,new IntRecord(val));
             }
             else
                 controller->appendRecord(cIndex,new wordRecord(dynamic_cast<QLineEdit*>(elementList[index])->text()));
            index++;
         }
 }
}
void MainWindow::OpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Scigli un file da aprire"),QDir::currentPath(),"*.xml");
    if(!filename.isEmpty())
    {
        OpenedFile=filename;
        controller->setTable(controller->loadModel(filename));
        qDebug()<<"before table show in main window";
        showDataTable();
        qDebug()<<"after table show in main window";

    }
}

void MainWindow::Close()
{
    if(controller->gotModified())
    {
        QMessageBox* toClose= new QMessageBox(QMessageBox::Question,"Nouvo File", tr("Vuoi salvare le modifiche prima di chiudere?"),
                                              QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, this);
        toClose->setButtonText(QMessageBox::Yes, tr("Sì"));
        toClose->setButtonText(QMessageBox::No, tr("No"));
        toClose->setButtonText(QMessageBox::Cancel, tr("Annulla"));
        toClose->setWindowFlags(toClose->windowFlags() & ~Qt::WindowCloseButtonHint);

        result = toClose->exec();

        if(result == QMessageBox::Yes)
        {
           MainWindow::Save();
           CloseFile();
        }
        else if(result == QMessageBox::No)
            CloseFile();
        else
            toClose->close();

    }
    else CloseFile();

    AddRowAction->setEnabled(false);
    RemoveRowAction->setEnabled(false);
    AddColAction->setEnabled(false);
    RemoveColAction->setEnabled(false);
    ChartAction->setEnabled(false);
    SaveAction->setEnabled(false);
    SaveAsAction->setEnabled(false);
    SaveModAction->setEnabled(false);
    CloseAction->setEnabled(false);
}

void MainWindow::OpenChart()
{
    qDebug()<<".............open chart calleed.........";
    saveRecords();
    CreateChartView* chartViewWid = new CreateChartView(this,controller);
    qDebug()<<"Before the exec of chartView";
    if(chartViewWid->exec())
    {
        tabs->addTab(chartViewWid->getChartView(),chartViewWid->getTitle());
        tabs->setMovable(true);
        ++tabsNum;
        tabs->setCurrentIndex(tabsNum);

        connect(tabs,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
      }

}

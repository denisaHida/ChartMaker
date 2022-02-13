#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Controller/controller.h"
#include "create1.h"
#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QString>
#include <QCloseEvent>
#include <QAction>
#include <QFile>
#include <QPushButton>
#include "tabview.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    private:
        Controller* controller;
        TabView* tabs;
        int tabsNum;
        int result;
        QString OpenedFile;
        QAction* NewAction;
        QAction* OpenAction;
        QAction* QuitAction;
        QAction* ChartAction;
        QAction* AddRowAction;
        QAction* RemoveRowAction;
        QAction* AddColAction;
        QAction* RemoveColAction;
        QAction* SaveModAction;
        QAction* CloseAction;
        QAction* SaveAction;
        QAction* SaveAsAction;
        QAction* remove;
        QMenu* FileMenu;
        QToolBar* File;
        void saveRecords();

    public:
         MainWindow(QWidget *parent = 0);
    public slots:
        void showDataTable();
    signals:
        void showData();
    private  slots:
         void NewFile();
         void OpenFile();
         void Close();
         void CloseFile();
         void OpenChart();
         void SaveAs();
         void Save();
         void closeTab(int);
         void addCol();
         void removeCol();
};

#endif // MAINWINDOW_H

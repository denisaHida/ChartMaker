#include "model.h"
#include <QXmlStreamWriter>
#include <QDebug>
Model::Model(Table*mT):mainTable(mT)
{

}

void Model::setMainTable(Table * mT)
{
    mainTable=mT;

}

void Model::save(QFile &file)
{
    qDebug() << "im in save";
    QXmlStreamWriter xmlWriter;
    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("MainTable");

    xmlWriter.writeTextElement("Titolo",mainTable->getTitle());

    xmlWriter.writeStartElement("Columns");

    for(unsigned int i=0;i<mainTable->getColumns().size() && !xmlWriter.hasError();i++)
    {
        qDebug() << "im in f1";

        xmlWriter.writeStartElement("Column");
        xmlWriter.writeTextElement("ColType",mainTable->getColumns()[i]->getType());
        xmlWriter.writeTextElement("ColTitle",mainTable->getColumns()[i]->getLabel());
        xmlWriter.writeStartElement("Records");
        for(int j=0;j<mainTable->getNumRows() && !xmlWriter.hasError();j++)
        {
            qDebug() << "f2";

            xmlWriter.writeTextElement("record",mainTable->getColumns()[i]->getRecords()[j]->getQStringValue());
//            xmlWriter.writeTextElement("record",h);
        }
        xmlWriter.writeEndElement();// records end

        xmlWriter.writeEndElement();// column end
    }
    xmlWriter.writeEndElement();// columns end
    xmlWriter.writeEndElement();// end maintable
    xmlWriter.writeEndDocument();
    if(xmlWriter.hasError())
    {
        qDebug() << "err";

        file.close();
        //throw ErrorSave();
    }
    else
    {
        //statusBar()->showMessage("Salvataggio dei dati",300);
        file.close();
    }
}

Table *Model::load(QString filename)
{
    Table* newTable = new Table();
    int nRows = 0;
    if(!filename.isEmpty())
    {
        QFile file(filename);
        QXmlStreamReader xmlreader(&file);
        if(file.open(QFile::ReadOnly)|| QFile::Text)
        {
            while(!xmlreader.atEnd() && !xmlreader.hasError())
            {
                QXmlStreamReader::TokenType token = xmlreader.readNext();
                if(token==QXmlStreamReader::StartDocument)
                    continue;
                if(xmlreader.isStartElement())
                {
                    if(xmlreader.name()=="MainTable")
                    {
                        qDebug()<<"found mainta" << xmlreader.name();
                        while(!xmlreader.atEnd() && !xmlreader.hasError())
                        {
                        xmlreader.readNext();
                        if(xmlreader.name()=="Titolo")
                            newTable->setTitle(xmlreader.readElementText());


                        vector<Column*> newColumns;
                        if(xmlreader.isStartElement())
                        {
                            if(xmlreader.name()=="Columns")
                            {
                                qDebug()<<"found cols";
                                while(!(xmlreader.tokenType()==xmlreader.EndElement))
                                {

                                    if(xmlreader.isStartElement())
                                    {
                                        if(xmlreader.name()=="Column")
                                        {
                                            qDebug()<<"found col";
                                            Column* newColumn = new Column();
                                            while(!(xmlreader.tokenType()==xmlreader.EndElement))
                                            {

                                            if(xmlreader.name()=="ColType")
                                            {
                                                qDebug()<<"found colType";
                                                newColumn->setType(xmlreader.readElementText());
                                                xmlreader.readNext();
                                            }
                                            if(xmlreader.name()=="ColTitle")
                                            {
                                                qDebug()<<"found colTitle";
                                                newColumn->setLabel(xmlreader.readElementText());
                                                xmlreader.readNext();
                                            }


                                            if(xmlreader.isStartElement())
                                            {

                                                if(xmlreader.name()=="Records")
                                                {
                                                    qDebug()<<"found records";
                                                    nRows = 0;
                                                    vector<Record*> newRecords;
                                                    while(!(xmlreader.tokenType()==xmlreader.EndElement))
                                                    {
                                                        if(xmlreader.name()=="record")
                                                        {
                                                            nRows++;
                                                            qDebug()<<"found record" << newColumn->getType();
                                                            if(newColumn->getType() == "intero")
                                                                newRecords.push_back(new IntRecord(xmlreader.readElementText().toInt()));
                                                            else if(newColumn->getType() == "decimale")
                                                                newRecords.push_back(new DoubleRecord(xmlreader.readElementText().toDouble()));
                                                            else
                                                                newRecords.push_back(new wordRecord(xmlreader.readElementText()));
                                                            qDebug()<<"record" << newRecords.back()->getQStringValue();

                                                        }
                                                            xmlreader.readNext();
                                                    }// records
                                                    newColumn->setRecords(newRecords);

                                                }

                                            }

                                            xmlreader.readNext();
                                            }
                                        newColumns.push_back(newColumn);
                                        }

                                    }
                                xmlreader.readNext();
                                }

                            }
                            newTable->setColumns(newColumns);
                        }
                        }
                    }
                }
            }
        }
    }
    qDebug()<<"in model newta" << newTable->getTitle();
    newTable->setNRows(nRows);
    return newTable;
}

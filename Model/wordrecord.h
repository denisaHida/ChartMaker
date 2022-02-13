#ifndef WORDRECORD_H
#define WORDRECORD_H
#include <QString>
#include "record.h"
using std::string;
class wordRecord : public Record
{
    QString value;
public:
    wordRecord(QString ="");
    ~wordRecord()=default;
    wordRecord* clone() const override;
    bool operator==(const Record &)const override;
    QString getValue() const;
    void setValue(const QString&);
    QString getQStringValue()const;
};

#endif // WORDRECORD_H

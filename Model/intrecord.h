#ifndef INTRECORD_H
#define INTRECORD_H
#include "record.h"

class IntRecord : public Record
{
    int value;
public:
    IntRecord(int val = 0.0);
    ~IntRecord()=default;
    IntRecord* clone() const override;
    bool operator==(const Record&)const override;
    void setValue(const int&);
    int getValue()const;
    QString getQStringValue()const;
};

#endif // INTRECORD_H

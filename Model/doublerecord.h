#ifndef DOUBLERECORD_H
#define DOUBLERECORD_H
#include "record.h"
class DoubleRecord: public Record
{
    double value;
public:
    DoubleRecord(double val = 0.0);
    DoubleRecord* clone() const override;
    ~DoubleRecord()=default;
    bool operator==(const Record&)const override;
    void setValue(const double&);
    double getValue()const;
    QString getQStringValue()const;

};

#endif // DOUBLERECORD_H

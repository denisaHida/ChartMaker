#ifndef NUMBERRECORD_H
#define NUMBERRECORD_H
#include "record.h"

class numberRecord : virtual public Record
{
public:
    numberRecord();
    //numberRecord* clone() const override;
    //bool operator==(const Record&)const override;
    //void setValue(const double&);
    //double getValue()const;
    //QString getQStringValue()const;


};

#endif // NUMBERRECORD_H

#ifndef RECORD_H
#define RECORD_H
#include <QString>

class Record
{
private:
public:
    Record();
    virtual ~Record()= default;
    virtual Record* clone() const=0;
    virtual bool operator==(const Record&)const=0;
//    virtual bool operator!=(const Record&)const=0;
    virtual QString getQStringValue()const=0;


};

#endif // RECORD_H

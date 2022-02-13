#include "wordrecord.h"

wordRecord::wordRecord(QString val):value(val)
{

}

wordRecord *wordRecord::clone() const
{
    return new wordRecord(*this);
}

bool wordRecord::operator==(const Record & r) const
{
       return value == r.getQStringValue();
}

QString wordRecord::getValue() const
{
    return value;
}

void wordRecord::setValue(const QString& val)
{
    value=val;
}

QString wordRecord::getQStringValue() const
{
    return value;
}

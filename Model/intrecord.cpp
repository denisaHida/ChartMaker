#include "intrecord.h"
IntRecord::IntRecord(int val):value(val)
{

}

IntRecord *IntRecord::clone() const
{
    return new IntRecord(*this);
}

bool IntRecord::operator==(const Record & r) const
{
    return value == r.getQStringValue().toInt();
}

void IntRecord::setValue(const int& val)
{
    value=val;
}

QString IntRecord::getQStringValue() const
{

    return QString::number(value);
}

int IntRecord::getValue() const
{
    return value;
}

#include "doublerecord.h"
DoubleRecord::DoubleRecord(double val):value(val)
{

}

DoubleRecord *DoubleRecord::clone() const
{
    return new DoubleRecord(*this);
}

bool DoubleRecord::operator==(const Record & r) const
{
    return value == r.getQStringValue().toDouble();
}

void DoubleRecord::setValue(const double& val)
{
    value=val;
}

QString DoubleRecord::getQStringValue() const
{

    return QString::number(value);
}



double DoubleRecord::getValue() const
{
    return value;
}


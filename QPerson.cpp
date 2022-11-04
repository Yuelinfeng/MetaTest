#include "QPerson.h"

QPerson::QPerson(QString name, QObject *parent) : QObject(parent)
{
    mName = name;
}

void QPerson::setAge(unsigned value)
{
    mAge = value;
    emit(ageChanged(mAge));
}

void QPerson::incAge()
{
    mAge++;
    emit(ageChanged(mAge));
}

unsigned QPerson::age()
{
    return mAge;
}

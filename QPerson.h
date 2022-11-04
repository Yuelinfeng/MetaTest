#ifndef QPERSON_H
#define QPERSON_H

#include <QObject>

class QPerson : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author","Yuelinfeng")
    Q_CLASSINFO("company","CQUPT")
    Q_CLASSINFO("version","1.0")

    Q_PROPERTY(unsigned age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(unsigned score MEMBER mScore)

private:
    unsigned mAge = 10;
    QString mName;
    unsigned mScore = 60;
public:
    explicit QPerson(QString name, QObject *parent = nullptr);

    unsigned age();
    void setAge(unsigned value);
    void incAge();
signals:
    ageChanged(unsigned value);
public slots:
};

#endif // QPERSON_H

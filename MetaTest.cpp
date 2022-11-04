#include "MetaTest.h"
#include "ui_MetaTest.h"
#include <QWidget>
#include <QMetaProperty>
MetaTest::MetaTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MetaTest)
{
    ui->setupUi(this);
    ui->spinBoy->setProperty("isBoy",true);
    ui->spinGirl->setProperty("isBoy",false);

    boy = new QPerson("王小明");
    boy->setProperty("score",95);
    boy->setProperty("age",10);
    boy->setProperty("sex","Boy");
    connect(boy, &QPerson::ageChanged, this, &MetaTest::on_ageChanged);

    girl = new QPerson("翠花");
    girl->setProperty("score",85);
    girl->setProperty("age",18);
    girl->setProperty("sex","Girl");
    connect(girl,&QPerson::ageChanged,this,&MetaTest::on_ageChanged);

    connect(ui->spinBoy,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));
    connect(ui->spinGirl,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));

    //清空文本框
    connect(ui->btnClear,&QPushButton::clicked,this,&MetaTest::clear_textEdit);
}

MetaTest::~MetaTest()
{
    delete ui;
}

void MetaTest::on_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(sender());
    if(spinBox->property("isBoy").toBool())
    {
        boy->setAge(spinBox->value());
    }
    else
    {
        girl->setAge(spinBox->value());
    }
}

void MetaTest::on_ageChanged(unsigned value)
{
    Q_UNUSED(value)
    QPerson *aPerson = qobject_cast<QPerson *>(sender());
    QString aName = aPerson->property("name").toString();
    QString aSex = aPerson->property("sex").toString();
    unsigned aAge = aPerson->age();
    ui->textEdit->append(aName+","+aSex
                                  +QString::asprintf(",年龄=%d",aAge));

}

void MetaTest::clear_textEdit()
{
    ui->textEdit->clear();
}

void MetaTest::on_btnBoyInc_clicked()
{
    boy->incAge();
}

void MetaTest::on_btnGirlInc_clicked()
{
    girl->incAge();
}

void MetaTest::on_btnClassInfo_clicked()
{
     const QMetaObject *meta = girl->metaObject();
     ui->textEdit->clear();
     ui->textEdit->append("==元对象信息==\n");
     ui->textEdit->append(QString("类名：%1\n").arg(meta->className()));
     ui->textEdit->append("property");
     for(int i = meta->propertyOffset();i < meta->propertyCount();i++)
     {
         QMetaProperty prop = meta->property(i);
         const char* propName = prop.name();
         QString propValue = boy->property(propName).toString();
         ui->textEdit->append(
                     QString("属性名称：%1，属性值：%2").arg(propName).arg(propValue));
     }
     ui->textEdit->append("");
     ui->textEdit->append("classInfo");
     for(int i = meta->classInfoOffset();i < meta->classInfoCount();i++)
     {
         QMetaClassInfo classInfo = meta->classInfo(i);
         ui->textEdit->append(QString("Name=%1 , Value=%2").arg(classInfo.name()).arg(classInfo.value()));
     }
}

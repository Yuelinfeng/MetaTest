#ifndef METATEST_H
#define METATEST_H

#include <QMainWindow>
#include "QPerson.h"
namespace Ui {
class MetaTest;
}

class MetaTest : public QMainWindow
{
    Q_OBJECT
private:
    QPerson *boy;
    QPerson *girl;
public:
    explicit MetaTest(QWidget *parent = 0);
    ~MetaTest();

private:
    Ui::MetaTest *ui;

    void on_ageChanged(unsigned value);
private slots:
    void clear_textEdit();
    void on_spin_valueChanged(int arg1);
    void on_btnBoyInc_clicked();
    void on_btnGirlInc_clicked();
    void on_btnClassInfo_clicked();
};

#endif // METATEST_H

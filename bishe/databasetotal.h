#ifndef DATABASETOTAL_H
#define DATABASETOTAL_H

#include <QWidget>

namespace Ui {
class databaseTotal;
}

class databaseTotal : public QWidget
{
    Q_OBJECT

public:
    explicit databaseTotal(QWidget *parent = 0);
    ~databaseTotal();

private:
    Ui::databaseTotal *ui;
};

#endif // DATABASETOTAL_H

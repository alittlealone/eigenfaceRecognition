#ifndef PICTURE_H
#define PICTURE_H

#include <QMainWindow>

namespace Ui {
class picture;
}

class picture : public QMainWindow
{
    Q_OBJECT

public:
    explicit picture(QWidget *parent = 0);
    ~picture();

private:
    Ui::picture *ui;
};

#endif // PICTURE_H

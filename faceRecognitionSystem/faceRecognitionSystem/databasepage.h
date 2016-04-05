#ifndef DATABASEPAGE_H
#define DATABASEPAGE_H

#include <QWidget>

namespace Ui {
	class DatabasePage;
};

class DatabasePage : public QWidget
{
	Q_OBJECT

public:
	DatabasePage(QWidget *parent = 0);
	~DatabasePage();

private:
	Ui::DatabasePage *ui;
};

#endif // DATABASEPAGE_H

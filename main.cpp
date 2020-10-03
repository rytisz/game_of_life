#include <QApplication>
#include <QTableView>
#include "mymodel.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTableView tableView;
	MyModel myModel;
	tableView.setModel(&myModel);
	tableView.show();

	return a.exec();
}

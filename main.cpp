#include <QApplication>
#include <QTableView>
#include <QHeaderView>

#include "mymodel.h"

void format_table(QTableView *tableView)
{
	tableView->horizontalHeader()->hide();
	tableView->verticalHeader()->hide();

	for (int i = 0; i < COLS; i++)
		tableView->setColumnWidth(i, 20);

	for (int i = 0; i < ROWS; i++)
		tableView->setRowHeight(i, 20);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTableView tableView;

	MyModel myModel;
	tableView.setModel(&myModel);
	format_table(&tableView);

	tableView.show();

	return a.exec();
}

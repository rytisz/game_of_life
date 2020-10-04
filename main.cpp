#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QHeaderView>
#include <QTableView>
#include <QTimer>

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

	QCommandLineParser parser;
	QCommandLineOption startState(QStringList() << "s" << "start-state",
			QCoreApplication::translate("main", "set starting state defined at <file>."),
			QCoreApplication::translate("main", "file"));
	parser.addOption(startState);

	parser.process(a);
	QString statePath = parser.value(startState);

	MyModel myModel;

	tableView.setModel(&myModel);
	if (myModel.setCurrentState(statePath))
		myModel.setCurrentState("patterns/penta-decathlon");

	format_table(&tableView);
	tableView.scrollTo(myModel.index(COLS/2, ROWS/2));

	tableView.show();

	return a.exec();
}

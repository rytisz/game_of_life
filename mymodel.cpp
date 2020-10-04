#include <QFile>
#include <QTextStream>
#include <fstream>
#include <qbrush.h>

#include "mymodel.h"
#include "debug.h"

MyModel::MyModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	currState = &stateBuf1;
	nextState = &stateBuf2;

	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			(*currState)[i][j] = false;

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MyModel::TimerSlot );
	timer->start(100);

	readState("patterns/penta-decathlon", currState);
}

void MyModel::TimerSlot()
{
	calculatetNextStates();
	swapStates();
}

void MyModel::swapStates()
{
	bool (*tmp)[COLS][ROWS];

	tmp = currState;
	currState = nextState;
	nextState = tmp;

	QModelIndex topLeft = createIndex(0,0);
	QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
	emit dataChanged(topLeft, bottomRight);
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
	return COLS;
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
	return ROWS;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
	int col = index.column();
	int row = index.row();

	switch (role) {
		case Qt::DisplayRole:
			return QString("%1").arg(getNeighbours(col, row));
		case Qt::BackgroundRole:
			if ((*currState)[col][row])
				return QBrush(Qt::black);
			else
				return QBrush(Qt::white);
	}

	return QVariant();
}

int MyModel::getNeighbours(const int col, const int row) const
{
	int count = 0;

	dprintf("\ncell [%d %d]:", col, row);
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			if ((i == 0) && (j == 0))
				continue;

			int nrow = row + i;
			int ncol = col + j;

			dprintf("\n\tneighbour [%d %d] ", ncol, nrow);

			if ((ncol < 0) || (ncol >= COLS))
				continue;
			if ((nrow < 0) || (nrow >= ROWS))
				continue;

			if ((*currState)[ncol][nrow]) {
				dprintf("alive");
				count++;
			}
		}
	dprintf("\n\tcount %d\n", count);

	return count;
}

void MyModel::calculatetNextStates()
{
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++) {
			int n = getNeighbours(i, j);

			if (n == 3)
				(*nextState)[i][j] = true;
			else if ((*currState)[i][j] && (n == 2))
				(*nextState)[i][j] = true;
			else
				(*nextState)[i][j] = false;
		}
}

void MyModel::readState(const QString path, bool (*state)[COLS][ROWS])
{
	memset(*state, 0, COLS * ROWS * sizeof(bool));

	QFile file(path);
	QString line;
	int j = 0;

	if (!file.open(QFile::ReadOnly | QFile::Text))
		return;

	QTextStream in(&file);

	while (!in.atEnd()) {
		line = in.readLine();
		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) == 'x')
				(*state)[i][j] = true;
		}
		j++;
	}
}

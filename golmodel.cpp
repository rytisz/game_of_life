#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <qbrush.h>

#include "golmodel.h"
#include "debug.h"

GOLModel::GOLModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	currState = &stateBuf1;
	nextState = &stateBuf2;

	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			(*currState)[i][j] = false;

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GOLModel::TimerSlot);
	timer->start(100);
}

void GOLModel::TimerSlot()
{
	calculatetNextStates();
	swapStates();
}

void GOLModel::swapStates()
{
	bool (*tmp)[COLS][ROWS];

	tmp = currState;
	currState = nextState;
	nextState = tmp;

	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
	emit dataChanged(topLeft, bottomRight);
}

int GOLModel::columnCount(const QModelIndex & /*parent*/) const
{
	return COLS;
}

int GOLModel::rowCount(const QModelIndex & /*parent*/) const
{
	return ROWS;
}

QVariant GOLModel::data(const QModelIndex &index, int role) const
{
	int col = index.column();
	int row = index.row();

	switch (role) {
		case Qt::DisplayRole:
			return QString("");
		case Qt::BackgroundRole:
			if ((*currState)[col][row])
				return QBrush(Qt::black);
			else
				return QBrush(Qt::white);
	}

	return QVariant();
}

int GOLModel::getNeighbours(const int col, const int row) const
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

void GOLModel::calculatetNextStates()
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

int GOLModel::readState(const QString path, bool (*state)[COLS][ROWS])
{
	memset(*state, 0, COLS * ROWS * sizeof(bool));

	QFile file(QCoreApplication::applicationDirPath() + "/" + path);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return -1;
	}

	QTextStream in(&file);
	QString line;

	int j = 0;

	while (!in.atEnd()) {
		line = in.readLine();
		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) == 'x')
				(*state)[i + COLS / 2][j + ROWS / 2] = true;
		}
		j++;
	}
	return 0;
}

int GOLModel::setCurrentState(const QString file)
{
	return readState(file, currState);
}

bool GOLModel::statesMatch()
{
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			if (stateBuf1[i][j] != stateBuf2[i][j])
				return false;

	return true;
}

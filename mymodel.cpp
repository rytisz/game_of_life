#include <qbrush.h>

#include "mymodel.h"

MyModel::MyModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	int i, j;

	for (int i = 0; i < COLS ; i++)
		for (int j = 0; j < ROWS; j++)
			isAlive[i][j] = false;

	isAlive[2][2]= true;
	isAlive[3][2]= true;
	isAlive[3][3]= true;
	isAlive[4][2]= true;
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
			return QString("%1").arg(getNeighbours(index));
		case Qt::BackgroundRole:
			if (isAlive[col][row])
				return QBrush(Qt::black);
			else
				return QBrush(Qt::white);
	}

	return QVariant();
}

int MyModel::getNeighbours(const QModelIndex &index) const
{
	int col = index.column();
	int row = index.row();

	int count = 0;

	printf("\ncell [%d %d]:", col, row);
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			if ((i == 0) && (j == 0))
				continue;

			int nrow = row + i;
			int ncol = col + j;

			printf("\n\tneighbour [%d %d] ", ncol, nrow);

			if ((ncol < 0) || (ncol >= COLS))
				continue;
			if ((nrow < 0) || (nrow >= ROWS))
				continue;

			if (isAlive[ncol][nrow]) {
				printf("alive");
				count++;
			}
			else
				printf("dead");
		}
	printf("\n\tcount %d\n", count);

	return count;
}

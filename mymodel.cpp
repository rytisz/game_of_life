#include <qbrush.h>

#include "mymodel.h"

MyModel::MyModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
	return ROWS;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
	return COLS;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int col = index.column();

	switch (role) {
		case Qt::DisplayRole:
			return QString("");
		case Qt::BackgroundRole:
			if (isAlive[row][col])
				return QBrush(Qt::black);
			else
				return QBrush(Qt::white);
	}

	return QVariant();
}

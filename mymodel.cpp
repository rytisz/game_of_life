#include "mymodel.h"

MyModel::MyModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
	return 300;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
	return 300;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
		return QString("");

	return QVariant();
}

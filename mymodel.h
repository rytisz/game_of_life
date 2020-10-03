#include <QAbstractTableModel>

const int COLS = 300;
const int ROWS = 300;

class MyModel : public QAbstractTableModel
{
	Q_OBJECT
	public:
		MyModel(QObject *parent = nullptr);
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		int columnCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		int getNeighbours(const QModelIndex &index) const;

	private:
		bool isAlive[COLS][ROWS];
};

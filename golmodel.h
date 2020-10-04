#include <QAbstractTableModel>
#include <QTimer>

const int COLS = 300;
const int ROWS = 300;

class GOLModel : public QAbstractTableModel
{
	Q_OBJECT
	public:
		GOLModel(QObject *parent = nullptr);
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		int columnCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		int setCurrentState(const QString file);

	private:
		bool stateBuf1[COLS][ROWS];
		bool stateBuf2[COLS][ROWS];

		bool (*currState)[COLS][ROWS];
		bool (*nextState)[COLS][ROWS];

		int getNeighbours(const int col, const int row) const;
		void calculatetNextStates();
		void swapStates();

		int readState(const QString path, bool (*state)[COLS][ROWS]);

		QTimer *timer;

	private slots:
		void TimerSlot();
};

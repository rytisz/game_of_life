#include <QtTest/QtTest>
#include "../golmodel.h"

class GOLTests : public QObject
{
	Q_OBJECT

private slots:
	void testBlock();
	void testPulsar();
	void testDecathlon();

};

void GOLTests::testBlock()
{
	GOLModel gol;

	gol.setCurrentState("../patterns/block");
	gol.calculatetNextStates();

	QVERIFY(gol.statesMatch());
}

void GOLTests::testPulsar()
{
	GOLModel gol;

	gol.setCurrentState("../patterns/pulsar");
	gol.calculatetNextStates();
	gol.swapStates();

	QVERIFY(gol.statesMatch() == false);

	for (int i = 0 ; i < 3; i++){
		gol.calculatetNextStates();
		gol.swapStates();
	}
	gol.setCurrentState("../patterns/pulsar");

	QVERIFY(gol.statesMatch());
}

void GOLTests::testDecathlon()
{
	GOLModel gol;

	gol.setCurrentState("../patterns/penta-decathlon");

	for (int i = 0 ; i < 16; i++){
		gol.calculatetNextStates();
		gol.swapStates();
	}
	gol.setCurrentState("../patterns/penta-decathlon");

	QVERIFY(gol.statesMatch());
}

 QTEST_MAIN(GOLTests)
#include "goltests.moc"

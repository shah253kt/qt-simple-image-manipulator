#include <QApplication>
#include <QTest>
#include "ImageContainerTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImageContainerTester tester;
    return QTest::qExec(&tester);
}

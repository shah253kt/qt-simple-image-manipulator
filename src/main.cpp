#include <QApplication>
#include <QFile>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set theme
    /*QFile styleSheetFile(":/theme/MailSy.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);*/

    MainWindow w;
    w.show();

    return app.exec();
}
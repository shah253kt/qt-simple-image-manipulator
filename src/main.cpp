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

    /*QWidget window;
    QImage myImage;
    myImage.load(":/resources/icon-folder-open.svg");
    qDebug() << "Image: " << myImage.isNull();
    myImage = myImage.scaledToHeight(300);

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(myImage));

    QVBoxLayout *windowLayout = new QVBoxLayout(&window);
    windowLayout->addWidget(&myLabel);
    
    window.show();*/

    MainWindow w;
    w.show();

    return app.exec();
}
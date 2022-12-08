#include <QApplication>
#include <QFile>
#include <QWidget>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set theme
    QFile styleSheetFile("./../theme/MailSy.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);

    QWidget window;
    window.show();

    return app.exec();
}
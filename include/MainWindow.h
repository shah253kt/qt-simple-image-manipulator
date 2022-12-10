#pragma once
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>

#define CLOCKWISE true
#define COUNTERCLOCKWISE !CLOCKWISE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QImage* loadedImage;
    QLabel* lblImageContainer;
    QVBoxLayout* centralLayout;
    qreal rotationAngle;
    bool flippedHorizontally, flippedVerically;

    void resizeEvent(QResizeEvent* event);

signals:
    void windowResized();
    void fileSelected();

public slots:
    void showFileDialog();
    void refreshImage();
    void rotateImage(bool clockwise);
    void flipImage(bool horizontally);
    void invertImage();
};

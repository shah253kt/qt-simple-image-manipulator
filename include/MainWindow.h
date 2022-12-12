#pragma once
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>

#include <QSharedPointer>
#include "ImageContainer.h"

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
    QSharedPointer<ImageContainer> imageContainer = QSharedPointer<ImageContainer>(new ImageContainer);
    QSharedPointer<QVBoxLayout> centralLayout;

    void resizeEvent(QResizeEvent* event);

signals:
    void windowResized();

public slots:
    void showFileDialog();
};

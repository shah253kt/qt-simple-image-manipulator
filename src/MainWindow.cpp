#include "MainWindow.h"
#include "./ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::showFileDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath() + '/' + QStandardPaths::displayName(QStandardPaths::PicturesLocation), tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "Selected file:" << fileName;

    if (fileName.length() > 0)
    {
        // Valid filename
    }
}


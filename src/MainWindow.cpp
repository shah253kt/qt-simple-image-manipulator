#include "MainWindow.h"
#include "./ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageContainer = QSharedPointer<ImageContainer>(new ImageContainer);
    centralLayout = QSharedPointer<QVBoxLayout>(new QVBoxLayout(ui->centralwidget));
    centralLayout->addWidget(imageContainer.get());

    QObject::connect(ui->actionAbout_Qt, &QAction::triggered, this, [this] { QMessageBox::aboutQt(this); }); // Show Qt about dialog
    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::showFileDialog); // Select image

    QObject::connect(this, &MainWindow::windowResized, imageContainer.get(), &ImageContainer::refreshImage); // Resize image when window is resized
    QObject::connect(ui->actionRotate_left, &QAction::triggered, this, [this] { imageContainer->rotateImage(COUNTERCLOCKWISE); }); // Rotate left
    QObject::connect(ui->actionRotate_right, &QAction::triggered, this, [this] { imageContainer->rotateImage(CLOCKWISE); }); // Rotate right
    QObject::connect(ui->actionFlip_horizontally, &QAction::triggered, this, [this] { imageContainer->flipImage(true); }); // Flip image horizontally
    QObject::connect(ui->actionFlip_vertically, &QAction::triggered, this, [this] { imageContainer->flipImage(false); }); // Flip image vertically
    QObject::connect(ui->actionInvert_pixel_values, &QAction::triggered, imageContainer.get(), &ImageContainer::invertImage); // Invert image
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    emit windowResized();
}

void MainWindow::showFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath() + '/' + QStandardPaths::displayName(QStandardPaths::PicturesLocation), tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "Selected file:" << fileName;

    if (fileName.length() > 0)
    {
        try
        {
            imageContainer->loadImage(fileName);
        }
        catch (ImageNotSupportedException)
        {
            QMessageBox::warning(this, "Image not supported", "Sorry, only grayscale images are supported.");
        }
    }
}

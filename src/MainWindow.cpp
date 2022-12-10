#include "MainWindow.h"
#include "./ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadedImage = new QImage;
    lblImageContainer = new QLabel;
    lblImageContainer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    lblImageContainer->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    centralLayout = new QVBoxLayout(ui->centralwidget);
    centralLayout->addWidget(lblImageContainer);

    QObject::connect(ui->actionAbout_Qt, &QAction::triggered, this, [this] { QMessageBox::aboutQt(this); }); // Show Qt about dialog
    QObject::connect(this, &MainWindow::windowResized, this, &MainWindow::refreshImage); // Resize image when window is resized
    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::showFileDialog); // Select image
    QObject::connect(ui->actionRotate_left, &QAction::triggered, this, [this] { rotateImage(COUNTERCLOCKWISE); }); // Rotate left
    QObject::connect(ui->actionRotate_right, &QAction::triggered, this, [this] { rotateImage(CLOCKWISE); }); // Rotate right
    QObject::connect(ui->actionFlip_horizontally, &QAction::triggered, this, [this] { flipImage(true); }); // Flip image horizontally
    QObject::connect(ui->actionFlip_vertically, &QAction::triggered, this, [this] { flipImage(false); }); // Flip image vertically
    QObject::connect(ui->actionInvert_pixel_values, &QAction::triggered, this, &MainWindow::invertImage); // Invert image
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    emit windowResized();
}

void MainWindow::refreshImage()
{
    lblImageContainer->setPixmap(QPixmap::fromImage(*loadedImage).transformed(QTransform().rotate(rotationAngle)).scaled(lblImageContainer->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::showFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath() + '/' + QStandardPaths::displayName(QStandardPaths::PicturesLocation), tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "Selected file:" << fileName;

    if (fileName.length() > 0)
    {
        loadedImage->load(fileName);
        rotationAngle = 0;
        flippedHorizontally = false;
        flippedVerically = false;
        refreshImage();
    }
}

void MainWindow::rotateImage(bool clockwise)
{
    qInfo() << "Rotating image" << (clockwise == CLOCKWISE ? "Clockwise" : "Counter-clockwise");

    rotationAngle += 90 * (clockwise ? 1 : -1);

    if (rotationAngle > 360)
        rotationAngle -= 360;
    else if (rotationAngle < 0)
        rotationAngle += 360;

    refreshImage();
}

void MainWindow::flipImage(bool horizontally)
{
    qInfo() << "Flipping image" << (horizontally ? "horizontally" : "vertically");
    loadedImage->mirror(horizontally, !horizontally);
    refreshImage();
}

void MainWindow::invertImage()
{
    qInfo() << "Inverting image";
    loadedImage->invertPixels();
    refreshImage();
}

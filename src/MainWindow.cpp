#include "MainWindow.h"
#include "./ui/ui_MainWindow.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

#include "ImageContainer.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageContainer = new ImageContainer;
    const auto centralLayout = new QVBoxLayout(ui->centralwidget);
    centralLayout->addWidget(imageContainer);

    connect(ui->actionAbout_Qt, &QAction::triggered, this, [this] { QMessageBox::aboutQt(this); }); // Show Qt about dialog
    connect(ui->actionAbout_This_Software, &QAction::triggered, this, &MainWindow::showAboutDialog); // Show about dialog
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::showFileDialog); // Select image

    connect(this, &MainWindow::windowResized, imageContainer, &ImageContainer::refreshImage); // Resize image when window is resized
    connect(ui->actionRotate_left, &QAction::triggered, this, [this] { imageContainer->rotateImage(false); }); // Rotate left
    connect(ui->actionRotate_right, &QAction::triggered, this, [this] { imageContainer->rotateImage(true); }); // Rotate right
    connect(ui->actionFlip_horizontally, &QAction::triggered, this, [this] { imageContainer->flipImage(true); }); // Flip image horizontally
    connect(ui->actionFlip_vertically, &QAction::triggered, this, [this] { imageContainer->flipImage(false); }); // Flip image vertically
    connect(ui->actionInvert_pixel_values, &QAction::triggered, imageContainer, &ImageContainer::invertImage); // Invert image
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
    const auto fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath() + '/' + QStandardPaths::displayName(QStandardPaths::PicturesLocation), tr("Image Files (*.png *.jpg *.jpeg *.bmp *.tif)"));
    qDebug() << "Selected file:" << fileName;

    if (!fileName.isEmpty())
    {
        try
        {
            imageContainer->loadImage(fileName);
        }
        catch (const ImageLoadFailedException &)
        {
            QMessageBox::warning(this, "Image load failed", "An error occurred during loading.");
        }
        catch (const ImageNotSupportedException &)
        {
            QMessageBox::warning(this, "Image not supported", "Sorry, only grayscale images are supported.");
        }
    }
}

void MainWindow::showAboutDialog()
{
    const QString title = "About this software";
    const QString content = "This is a project built using Qt6 for simple image manipulation.\n\
        This project was meant to simply learn about using Qt framework and CMake.<br><br>";
    const QString credits = "<br><br>Credits to <a href='https://fontawesome.com/'>Font Awesome</a> and <a href='https://www.iconninja.com/avatar-ninja-samurai-warrior-icon-14586'>iconninja</a> their amazing icons.";
    QIcon icon;
    icon.addFile(":/resources/ninja.png");

    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setIcon(QMessageBox::Icon::Information);
    msgBox.setWindowIcon(icon);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(content + "Checkout the <a href='https://github.com/shah253kt/qt-simple-image-manipulator'>project repository here</a>." + credits);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

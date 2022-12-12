#include "ImageContainer.h"

ImageContainer::ImageContainer(QWidget *parent)
	: QLabel(parent), rotationAngle(0)
{
	this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

ImageContainer::~ImageContainer()
{}

void ImageContainer::loadImage(QString filename)
{
	if (!image->load(filename) || !image->isGrayscale()) {
		throw ImageNotSupportedException();
	}
	
	rotationAngle = 0;
	refreshImage();
}

// -------------------------------------------------------------------------------------
// Slots
// -------------------------------------------------------------------------------------
void ImageContainer::refreshImage()
{
	this->setPixmap(QPixmap::fromImage(*image).transformed(QTransform().rotate(rotationAngle)).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageContainer::rotateImage(bool clockwise)
{
	qInfo() << "Rotating image" << (clockwise == CLOCKWISE ? "Clockwise" : "Counter-clockwise");

	rotationAngle += 90 * (clockwise ? 1 : -1);

	if (rotationAngle > 360)
		rotationAngle -= 360;
	else if (rotationAngle < 0)
		rotationAngle += 360;

	refreshImage();
}

void ImageContainer::flipImage(bool horizontally)
{
	qInfo() << "Flipping image" << (horizontally ? "horizontally" : "vertically");
	image->mirror(horizontally, !horizontally);
	refreshImage();
}

void ImageContainer::invertImage()
{
	qInfo() << "Inverting image";
	image->invertPixels();
	refreshImage();
}

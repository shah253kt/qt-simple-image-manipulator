#include "ImageContainer.h"

#include "ImageProc.h"

ImageContainer::ImageContainer(QWidget *parent)
	: QLabel(parent)
{
	this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void ImageContainer::loadImage(const QString &filename)
{
	if (!image.load(filename))
	{
		throw ImageLoadFailedException();
	}

    if (!image.isGrayscale())
	{
		throw ImageNotSupportedException();
	}

	refreshImage();
}

// -------------------------------------------------------------------------------------
// Slots
// -------------------------------------------------------------------------------------
void ImageContainer::refreshImage()
{
	this->setPixmap(QPixmap::fromImage(image).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageContainer::rotateImage(bool clockwise)
{
	qInfo() << "Rotating image" << (clockwise ? "Clockwise" : "Counter-clockwise");
	image = ImageProc::rotateImageBy90Degrees(image, clockwise);
	refreshImage();
}

void ImageContainer::flipImage(bool horizontally)
{
	qInfo() << "Flipping image" << (horizontally ? "horizontally" : "vertically");
	image = ImageProc::flipImage(image, horizontally);
	refreshImage();
}

void ImageContainer::invertImage()
{
	qInfo() << "Inverting image";
	image = ImageProc::invertImage(image);
	refreshImage();
}

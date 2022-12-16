#pragma once

#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSharedPointer>
#include <QException>

#define CLOCKWISE true
#define COUNTERCLOCKWISE !CLOCKWISE

class ImageNotSupportedException : public QException
{
public:
    void raise() const override { throw* this; }
    ImageNotSupportedException* clone() const override { return new ImageNotSupportedException(*this); }
};

class ImageContainer  : public QLabel
{
	Q_OBJECT

private:
	QSharedPointer<QImage> image = QSharedPointer<QImage>(new QImage);
    qreal rotationAngle;

public:
	ImageContainer(QWidget *parent = nullptr);
	~ImageContainer();
    void loadImage(QString filename);

public slots:
    void refreshImage();
    qreal rotateImage(bool clockwise);
    void flipImage(bool horizontally);
    void invertImage();
};

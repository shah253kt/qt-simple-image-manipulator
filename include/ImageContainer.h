#pragma once

#include <QLabel>
#include <QImage>
#include <QException>

class ImageLoadFailedException : public QException
{
public:
    void raise() const override { throw* this; }
    [[nodiscard]] ImageLoadFailedException* clone() const override { return new ImageLoadFailedException(*this); }
};

class ImageNotSupportedException : public QException
{
public:
    void raise() const override { throw* this; }
    [[nodiscard]] ImageNotSupportedException* clone() const override { return new ImageNotSupportedException(*this); }
};

class ImageContainer final : public QLabel
{
	Q_OBJECT

public:
	explicit ImageContainer(QWidget *parent = nullptr);
	~ImageContainer() override = default;
    void loadImage(const QString &filename);

private:
	QImage image;

public slots:
    void refreshImage();
    void rotateImage(bool clockwise);
    void flipImage(bool horizontally);
    void invertImage();
};

#include "ImageContainerTester.h"

ImageContainerTester::ImageContainerTester(QObject* parent) : QObject(parent)
{
}

void ImageContainerTester::initTestCase()
{
    imageContainer = QSharedPointer< ImageContainer>(new ImageContainer);
}

void ImageContainerTester::testLoadImage()
{
    QVERIFY_THROWS_NO_EXCEPTION(imageContainer->loadImage(":/resources/example-1-lazy-dog.png"));
    QVERIFY_THROWS_NO_EXCEPTION(imageContainer->loadImage(":/resources/example-2-led-floodlight.png"));
    QVERIFY_THROWS_NO_EXCEPTION(imageContainer->loadImage(":/resources/ninja-grayscale-8-bit.png"));
    QVERIFY_THROWS_NO_EXCEPTION(imageContainer->loadImage(":/resources/ninja-grayscale-16-bit.png"));
    QVERIFY_THROWS_NO_EXCEPTION(imageContainer->loadImage(":/resources/ninja-grayscale-8-bits.jpg"));
    QVERIFY_THROWS_NO_EXCEPTION(imageContainer->loadImage(":/resources/ninja-grayscale-16-bits.jpg"));
    QVERIFY_THROWS_EXCEPTION(ImageNotSupportedException, imageContainer->loadImage(":/resources/landscape.jpeg"));
    QVERIFY_THROWS_EXCEPTION(ImageNotSupportedException, imageContainer->loadImage(":/resources/ninja.png"));
}

void ImageContainerTester::testRotateImage()
{
    QCOMPARE(imageContainer->rotateImage(CLOCKWISE), 90);
    QCOMPARE(imageContainer->rotateImage(CLOCKWISE), 180);
    QCOMPARE(imageContainer->rotateImage(CLOCKWISE), 270);
    QCOMPARE(imageContainer->rotateImage(CLOCKWISE), 0);
    QCOMPARE(imageContainer->rotateImage(COUNTERCLOCKWISE), 270);
    QCOMPARE(imageContainer->rotateImage(COUNTERCLOCKWISE), 180);
    QCOMPARE(imageContainer->rotateImage(COUNTERCLOCKWISE), 90);
    QCOMPARE(imageContainer->rotateImage(COUNTERCLOCKWISE), 0);
}

void ImageContainerTester::cleanupTestCase(){
}

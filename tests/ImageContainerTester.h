#pragma once

#include <QObject>
#include <QTest>
#include <QSharedPointer>
#include "ImageContainer.h"

class ImageContainerTester : public QObject
{
    Q_OBJECT
private:
    QSharedPointer<ImageContainer> imageContainer;

public:
    explicit ImageContainerTester(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();
    void testLoadImage();
    void testRotateImage();
    void cleanupTestCase();
};
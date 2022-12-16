#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageContainer;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
    ImageContainer *imageContainer;

    void resizeEvent(QResizeEvent* event) override;

signals:
    void windowResized();

public slots:
    void showFileDialog();
    static void showAboutDialog();
};

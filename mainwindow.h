#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fileRenderButton_clicked();
    void on_screenRenderButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;  //pointer to image displayed on screen
    QPixmap image;
};

#endif // MAINWINDOW_H

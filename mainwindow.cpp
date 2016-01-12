#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mandelbrot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Rendering...");
    //render images
    renderMandelbrot(ui->renderTypeBox->currentIndex());
    ui->label->setText("Done!");
}

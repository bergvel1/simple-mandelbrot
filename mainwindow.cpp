#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mandelbrot.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    //delete renderedImage;
    delete scene;
    delete ui;
}

void MainWindow::on_fileRenderButton_clicked()
{
    //render image
    QImage renderedImage = renderMandelbrot(ui->renderTypeBox->currentIndex());

    //save to file
    bool goodSave = renderedImage.save("save.bmp", 0, -1);  //TODO: make filename reflect render type
    if(goodSave) std::cout << "Render successfully saved" << std::endl;
    else std::cout << "error saving image" << std::endl;
}

void MainWindow::on_screenRenderButton_clicked()
{
    //render image
    QImage renderedImage = renderMandelbrot(ui->renderTypeBox->currentIndex());

    //save to file
    bool goodSave = renderedImage.save("temp.bmp", 0, -1);
    if(goodSave) std::cout << "temp image successfully saved" << std::endl;
    else std::cout << "error saving image" << std::endl;

    //load from file and display
    image.load("temp.bmp");
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());

    ui->mainImage->setScene(scene);

    //delete file
    if(remove("temp.bmp") != 0)
        std::cout << "Error deleting temp image" << std::endl;
    else
        std::cout << "Temp image successfully deleted" << std::endl;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(ui->openGLWidget->width(), ui->openGLWidget->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

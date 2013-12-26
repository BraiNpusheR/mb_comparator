#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridLayout->setMargin(10);
    ui->gridLayout->addWidget(ui->textEdit);
    ui->centralWidget->setLayout(ui->gridLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

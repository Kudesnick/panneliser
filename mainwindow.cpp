#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSplitter *base = new QSplitter(this);
    ui->gridLayout->addWidget(base);
    new Panel(base, "*");
}

MainWindow::~MainWindow()
{
    delete ui;
}

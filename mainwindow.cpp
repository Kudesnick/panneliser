#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Splitter *base = new Splitter(this);
    ui->gridLayout->addWidget(base);
    base->addWidget(new Panel(base, "*"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

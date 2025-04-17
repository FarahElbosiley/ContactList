#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include"ContactList.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_collapsed(const QModelIndex &index)
{
    // Your slot implementation here
}




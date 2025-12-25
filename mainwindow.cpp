#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{

}


void MainWindow::on_extractButton_clicked()
{

}


void MainWindow::on_nameInput_editingFinished()
{

}


void MainWindow::on_conditionInput_textChanged()
{

}


void MainWindow::on_ageInput_valueChanged(int arg1)
{

}


void MainWindow::on_riskInput_valueChanged(int arg1)
{

}


void MainWindow::on_waitingListTable_itemSelectionChanged()
{

}


void MainWindow::on_statusLabel_linkActivated(const QString &link)
{

}


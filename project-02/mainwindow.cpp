#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonTab1->setProperty("pagematches",true);
    ui->pushButtonTab2->setProperty("pagematches",false);
    ui->pushButtonTab3->setProperty("pagematches",false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
  // Set all buttons to false
  ui->pushButtonTab1->setProperty("pagematches",false);
  ui->pushButtonTab2->setProperty("pagematches",false);
  ui->pushButtonTab3->setProperty("pagematches",false);

  // Set one of the buttons to true
  switch (index) {
  case 0:
    ui->pushButtonTab1->setProperty("pagematches",true);
    break;
  case 1:
    ui->pushButtonTab2->setProperty("pagematches",true);
    break;
  case 2:
    ui->pushButtonTab3->setProperty("pagematches",true);
    break;
  }

  // Update buttons style
  ui->pushButtonTab1->style()->polish(ui->pushButtonTab1);
  ui->pushButtonTab2->style()->polish(ui->pushButtonTab2);
  ui->pushButtonTab3->style()->polish(ui->pushButtonTab3);
}

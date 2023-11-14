#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../../../1sql/db/lite.db");

    if (db.open()) {

        ui->statusbar->showMessage("Connection with SQLite was success!");
         model = new QSqlTableModel(this, db);
         model->setTable("USERS");
         model->select();

         ui->tableView->setModel(model);
    }
    else ui->statusbar->showMessage("Error: "+ db.lastError().databaseText());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QFile file("C:\\conspect.txt");
    if(!file.open(QIODevice::ReadOnly) && !file.open(QIODevice::WriteOnly))
        QMessageBox::information(0, "info", file.errorString());

    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
}


void MainWindow::on_Base_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_Remove_clicked()
{
    model->revertRow(curentRow);
    model->select();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    curentRow = index.row();
}



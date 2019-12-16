#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <rsa.h>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete rsa;
}


void MainWindow::on_encryptButton_clicked()
{
    ui->statusbar->showMessage("Encrypt", 3000);

    QString sourceText = ui->sourceTextEdit->toPlainText();

    std::string text = sourceText.toUtf8().constData();

    std::string str = rsa->encrypt(text);

    QString qstr = QString::fromStdString(str);

    ui->resultTextEdit->setText(qstr);
}

void MainWindow::on_decryptButton_clicked()
{
    ui->statusbar->showMessage("Decrypt", 3000);

    QString sourceText = ui->sourceTextEdit->toPlainText();

    std::string text = sourceText.toUtf8().constData();

    std::string str = rsa->decrypt(text);

    QString qstr = QString::fromStdString(str);

    ui->resultTextEdit->setText(qstr);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);
    img = new QPixmap;
    request = new Request;
    // setFixedSize(606, 469);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::done() {
    QString login = request->response.value("login").toString();
    // QString login = request->response.value("message").toString();
    qDebug() << "login?" << login;
}

void MainWindow::userName() {
    request->get(QString("https://api.github.com/users/%1").arg(ui->searchBar->text()));
    // request->get(QString("https://api.twitch.tv/"));
    connect(request->net_reply, &QNetworkReply::finished, this, &MainWindow::done);
}

void MainWindow::on_searchButton_clicked() {
    QString firstName = ui->searchBar->text();
    userName();
}

void MainWindow::on_searchBar_returnPressed() {
    on_searchButton_clicked();
}

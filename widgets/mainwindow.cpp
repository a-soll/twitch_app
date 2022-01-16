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
    user = new User;
    request = new Request;
    // setFixedSize(606, 469);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::read_data() {
    data_buffer.append(net_reply->readAll());
}

void MainWindow::finished_reading() {
    QJsonObject response;
    if (net_reply->error() != QNetworkReply::NoError) {
        response = QJsonDocument::fromJson(data_buffer).object();
        qDebug(qPrintable(net_reply->errorString()));
    } else {
        response = QJsonDocument::fromJson(data_buffer).object();
        qDebug() << "resp: " << response.value("login").toString();
    }
    data_buffer.clear();
}

void MainWindow::done() {
    QString login = request->response.value("login").toString();
    // QString login = request->response.value("message").toString();
    qDebug() << "login?" << login;
}

void MainWindow::userName() {
    User u;
    // QNetworkRequest req;
    // req.setUrl(QString("https://api.github.com/users/%1").arg("a-soll"));
    // net_reply = netManager->get(req);
    // request->get(QString("https://api.github.com/users/%1").arg(ui->searchBar->text()));

    // u.get_followed_channels();
    // connect(net_reply, &QNetworkReply::readyRead, this, &MainWindow::read_data);
    // connect(net_reply, &QNetworkReply::finished, this, &MainWindow::finished_reading);

    // QNetworkAccessManager *manager = new QNetworkAccessManager;
    // QNetworkRequest req(QString("https://api.github.com/users/%1").arg(ui->searchBar->text()));
    // QNetworkReply *reply = manager->get(req);

    request->get(QString("https://api.github.com/users/%1").arg("a-soll"));
    connect(request, &Request::finished, this, &MainWindow::done);
}

void MainWindow::on_searchButton_clicked() {
    QString firstName = ui->searchBar->text();
    user->get_followed_channels();
    // userName();
}

void MainWindow::on_searchBar_returnPressed() {
    on_searchButton_clicked();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QtWidgets/QDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // sidebar = new SideBar;
    model = new QStandardItemModel;
    // img = new QPixmap;
    // appUser = new User(User::get_user("42045317"));
    appUser = new User("42045317");
    // appUser->id = "42045317";
    request = new Request;
    player = new QMediaPlayer;
    appUser->get_followed_channels();
    // QVideoWidget *vid = new QVideoWidget(ui->vidWidget);
    vid = new QVideoWidget(ui->vidWidget);
    connect(appUser, &User::finished, this, &MainWindow::populate_follow_bar);
    play();
}

MainWindow::~MainWindow() {
    delete ui;
    delete appUser;
    delete request;
    delete model;
}

void MainWindow::read_data() {
    data_buffer.append(net_reply->readAll());
}

void MainWindow::finished_reading() {
    QJsonObject response;
    if (net_reply->error() != QNetworkReply::NoError) {
        response = QJsonDocument::fromJson(data_buffer).object();
        // qDebug(qPrintable(net_reply->errorString()));
        qDebug() << net_reply->errorString();
    } else {
        response = QJsonDocument::fromJson(data_buffer).object();
        qDebug() << "resp: " << response.value("login").toString();
    }
    data_buffer.clear();
}

void MainWindow::done() {
    QString login = request->response.value("login").toString();
    QJsonDocument d(request->response);
    QString s(d.toJson(QJsonDocument::Indented));
    // qDebug() << "yo: " << s;
    // QString login = request->response.value("message").toString();
    qDebug() << "login?" << login;
}

void MainWindow::userName() {
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

    // request->get(QString("https://api.github.com/users/%1").arg("a-soll"));
    // connect(request->net_reply, &QNetworkReply::finished, this, &MainWindow::done);
    appUser->get_followed_channels();
    // qDebug() << appUser->followed.at(0).thumnail_url;
}

void MainWindow::on_searchButton_clicked() {
    QString firstName = ui->searchBar->text();
    // appUser->get_followed_channels();
    userName();
}

void MainWindow::on_searchBar_returnPressed() {
    on_searchButton_clicked();
}

void MainWindow::populate_follow_bar() {
    QFont font("Helvetica", 18);
    ui->sideBar->setFont(font);
    ui->sideBar->setModel(model);
    QList<QStandardItem *> list_item;
    for (auto it = begin(appUser->followed); it != end(appUser->followed); ++it) {
        Channel *chan = it.operator*();
        User *u = new User(chan->user_id);
        QStandardItem *item = new QStandardItem;
        item->setFont(font);
        item->setText(chan->user_name);
        list_item.append(item);
        delete u;
    }
    model->appendColumn(list_item);
}

void MainWindow::play() {
    // QVideoWidget *vidw = new QVideoWidget;
    qDebug() << vid->frameGeometry().height();
    vid->setMinimumWidth(500);
    vid->setMinimumHeight(500);
    player->setSource(QUrl::fromLocalFile("/Users/adam/Downloads/yt5s.com-So I Tried Lost Ark...-(1080p).mp4"));

    player->setVideoOutput(vid);

    vid->show();
    player->play();
}

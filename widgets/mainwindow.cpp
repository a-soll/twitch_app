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
    sidebar = new SideBar;
    // img = new QPixmap;
    // appUser = new User(User::get_user("42045317"));
    appUser = new User("42045317");
    // appUser->id = "42045317";
    request = new Request;
    appUser->get_followed_channels();
    connect(appUser, &User::finished, this, &MainWindow::populate_follow_bar);
}

MainWindow::~MainWindow() {
    delete ui;
    delete appUser;
    delete request;
    delete sidebar;
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
    // QListView sidebar = ui->listView;
    // QStringList list;
    QStandardItemModel *model = new QStandardItemModel;
    sidebar->setModel(model);
    QList<QStandardItem *> list_item;
    // QStringListModel *model = new QStringListModel();
    QFont font("Helvetica", 18);
    // sidebar->setFont(font);
    sidebar->setMouseTracking(true);

    for (auto it = begin(appUser->followed); it != end(appUser->followed); ++it) {
        Channel *chan = it.operator*();
        User *u = new User(chan->user_id);
        // u->get_profile_image();
        // img.loadFromData();
        QStandardItem *item = new QStandardItem;
        item->setFont(font);
        item->setText(chan->user_name);
        list_item.append(item);
        // list.append(chan->user_name);
    }
    model->appendColumn(list_item);
}

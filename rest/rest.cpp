#include "rest.h"

QString Request::base_url = QString("https://api.twitch.tv/helix");
QSettings Request::settings = QSettings(QString("secret.ini"), QSettings::IniFormat);
QString Request::client_id = Request::settings.value("client").toString();
QString Request::user_token = Request::settings.value("token").toString();

Request::Request(QObject *parent) : QObject(parent) {
    net_manager = new QNetworkAccessManager;
    net_reply = nullptr;
    req = new QNetworkRequest;
}

Request::~Request() {
    delete net_manager;
    delete req;
}

void Request::read_data() {
    data_buffer.append(net_reply->readAll());
}

void Request::set_custom_header(QString key, QString value) {
    req->setRawHeader(key.toLocal8Bit(), value.toLocal8Bit());
}

void Request::finished_reading() {
    if (net_reply->error() != QNetworkReply::NoError) {
        response = QJsonDocument::fromJson(data_buffer).object();
        QJsonDocument doc(response);
        QString sj(doc.toJson(QJsonDocument::Indented));
        qDebug() << "Error: " << sj;
    } else {
        response = QJsonDocument::fromJson(data_buffer).object();
    }
    data_buffer.clear();
    emit finished();
}

void Request::get(QString url) {
    req->setUrl(url);
    qDebug() << "url: " << url;
    net_reply = net_manager->get(*req);
    QObject::connect(net_reply, &QNetworkReply::readyRead, this, &Request::read_data);
    QObject::connect(net_reply, &QNetworkReply::finished, this, &Request::finished_reading);
}

// void Request::get_user_followers(QString user_id) {
//     QString uri = QString("%1/streams/followed?user_id=%2").arg(Request::base_url).arg(user_id);
//     get(uri);
    // Request::get(uri);
    // connect(&Request::net_reply, &QNetworkReply::finished, this, &Request::finished_reading);
// }

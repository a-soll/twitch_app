#include "rest.h"

QString Request::base_url = QString("https://api.twitch.tv/helix");

Request::Request(QNetworkRequest *parent) {
    net_manager = new QNetworkAccessManager(this);
    net_reply = nullptr;
    req = new QNetworkRequest;
    get_settings();
}

void Request::get_settings() {
    QSettings settings(QString("secret.ini"), QSettings::IniFormat);
    client_id = settings.value("client").toString();
    user_token = settings.value("token").toString();
    qDebug() << "id: " << client_id;
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
    connect(net_reply, &QNetworkReply::readyRead, this, &Request::read_data);
    connect(net_reply, &QNetworkReply::finished, this, &Request::finished_reading);
}

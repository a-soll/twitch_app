#include "rest.h"

const QString Request::base_url = "https://api.twitch.tv/helix";

Request::Request(QNetworkRequest *parent) {
    net_manager = new QNetworkAccessManager(this);
    net_reply = nullptr;
}

void Request::read_data() {
    data_buffer.append(net_reply->readAll());
}

void Request::finished_reading() {
    if (net_reply->error() != QNetworkReply::NoError) {
        response = QJsonObject();
        qDebug() << "Error:" << net_reply->Text;
    } else {
        response = QJsonDocument::fromJson(data_buffer).object();
        qDebug() << "resp: " << response.value("login").toString();
    }
    data_buffer.clear();
    emit finished();
}

void Request::get(QString url) {
    QNetworkRequest req{QUrl(url)};

    net_reply = net_manager->get(req);
    connect(net_reply, &QNetworkReply::readyRead, this, &Request::read_data);
    connect(net_reply, &QNetworkReply::finished, this, &Request::finished_reading);
}

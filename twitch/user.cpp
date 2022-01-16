#include "user.h"

User::User(QObject *parent) {
    url = Request::base_url + "/channels";
    request = new Request;
    id = "42045317";
}

void User::done() {
    QJsonDocument doc(request->response);
    QString sj(doc.toJson(QJsonDocument::Indented));
    qDebug().noquote() << "user: " << sj;
}

void User::get_followed_channels() {
    QString uri = QString("%1/streams/followed?user_id=%2").arg(Request::base_url).arg(id);
    request->set_custom_header(QString("Client-ID"), request->client_id);
    request->set_custom_header(QString("Authorization"), QString("Bearer " + request->user_token));
    // QNetworkAccessManager manager;
    // QNetworkReply *reply;

    // request.setRawHeader("Authentication", bearer.toLocal8Bit());
    request->get(uri);
    connect(request->net_reply, &QNetworkReply::finished, this, &User::done);
}

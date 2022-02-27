#include "user.h"
#include <QCoreApplication>

User::User(QString id_param, QObject *parent) : QObject(parent) {
    url = Request::base_url + "/channels";
    request = new Request;
    request->set_custom_header(QString("Client-ID"), Request::client_id);
    request->set_custom_header(QString("Authorization"), QString("Bearer " + Request::user_token));
    id = id_param;
}

User::~User() {
    delete request;
    for (auto it = begin(followed); it != end(followed); ++it) {
        delete it.operator*();
    }
}

void User::request_finished() {
    QJsonDocument doc(request->response);
    QString sj(doc.toJson(QJsonDocument::Indented));
    qDebug() << sj;
}

void User::populate_follows() {
    QJsonArray arr = request->response["data"].toArray();
    QJsonArray::const_iterator i;
    for (i = arr.begin(); i != arr.end(); i++) {
        QJsonValueRef chan = i.operator*();
        Channel *follow = new Channel(chan.toObject());
        followed.push_back(follow);
        // qDebug() << follow->id;
    }
    emit finished();
}

void User::get_followed_channels() {
    QString uri = QString("%1/streams/followed?user_id=%2").arg(Request::base_url).arg(id);
    request->get(uri);
    connect(request->net_reply, &QNetworkReply::finished, this, &User::populate_follows);
    // qDebug() << request->response;
}

void User::get_profile_image() {
    qDebug() << profile_image_url;
    request->get(profile_image_url);
    connect(request->net_reply, &QNetworkReply::finished, this, &User::request_finished);
}

QJsonObject User::get_user(QString user_id) {
    QString url = "https://api.twitch.tv/helix/users";

}

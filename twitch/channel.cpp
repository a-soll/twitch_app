#include "channel.h"

Channel::Channel(QJsonObject json, QObject *parent) {
    populate(json);
    request = new Request;
    request->set_custom_header(QString("Client-ID"), Request::client_id);
    request->set_custom_header(QString("Authorization"), QString("Bearer " + Request::user_token));
}

Channel::~Channel() {
    delete request;
}

void Channel::get_channel(QString channel_id) {
}

void Channel::populate(QJsonObject json) {
    id = json.value("id").toString();
    game_id = json.value("game_id").toString();
    is_live = json.value("is_live").toBool();
    is_mature = json.value("is_mature").toBool();
    viewer_count = json.value("viewer_count").toInt();
    user_id = json.value("user_id").toString();
    started_at = json.value("started_at").toString();
    title = json.value("title").toString();
    user_login = json.value("user_login").toString();
    user_name = json.value("user_name").toString();
    thumnail_url = json.value("thumbnail_url").toString();
}

void Channel::get_thumbail() {
    QString url = thumnail_url;
    request->get(url);
}

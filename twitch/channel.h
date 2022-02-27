#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include "rest/rest.h"

class Channel : public QObject {
    Q_OBJECT;

public:
    Channel(QJsonObject json, QObject *parent = nullptr);
    ~Channel();
    void get_channel(QString channel_id);
    void populate(QJsonObject json);
    void get_thumbail();

    bool is_live;
    bool is_mature;
    QString id;
    QString game_id;
    int viewer_count;
    QString user_id;
    QString started_at;
    QString title;
    QString user_login;
    QString user_name;
    QString thumnail_url;

signals:
    void finished();
private:
    Request *request;
};

#endif /* CHANNEL_H */

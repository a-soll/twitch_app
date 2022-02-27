#ifndef USER_H
#define USER_H

#include "twitch/channel.h"
#include "rest/rest.h"
#include <QObject>

class User : public QObject{
    Q_OBJECT

public:
    User(QString id_param, QObject *parent = 0);
    ~User();
    void get_followed_channels();
    void get_profile_image();
    static QJsonObject get_user(QString user_id);

    QString id;
    QString name;
    QString profile_image_url;
    std::vector<Channel*> followed;

signals:
    void finished();

private:
    void request_finished();
    void populate_follows();

    QString url;
    Request *request;
};

#endif /* USER_H */

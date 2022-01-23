#ifndef USER_H
#define USER_H

#include "twitch/channel.h"
#include "rest/rest.h"
#include <QObject>

class User : public QObject {
    Q_OBJECT;

public:
    User(QObject *parent = nullptr);
    void get_followed_channels();

    QString id;
    QString name;
    std::vector<Channel> followed;

private:
    void request_finished();

    QString url;
    Request *request;
};

#endif /* USER_H */

#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QString>

class Channel : public QObject {
    Q_OBJECT;

public:
    Channel(QObject *parent = nullptr);
    void get_channel(QString channel_id);

    bool is_live;
    int id;
    int game_id;
    int viewer_count;
    int user_id;
    QString started_at;
    QString title;
    QString user_login;
    QString user_name;
    QString thumnail_url;
};

#endif /* CHANNEL_H */

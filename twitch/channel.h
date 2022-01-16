#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <QObject>

class Channel : public QObject {
    Q_OBJECT;

public:
    Channel(QObject *parent = nullptr);
    void get_channel(QString channel_id);

    QString id;
};

#endif /* CHANNEL_H */

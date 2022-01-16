#ifndef REST_H
#define REST_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkReply>

class Request : public QObject {
    Q_OBJECT;

public:
    Request(QNetworkRequest *parent = nullptr);
    // ~Request();
    static const QString base_url;
    QJsonObject response;
    QNetworkReply *net_reply;

private slots:
    void read_data();
    void finished_reading();

public slots:
    void get(QString url);

signals:
    void finished();

private:
    QByteArray data_buffer;
    QNetworkAccessManager *net_manager;
};

#endif /* REST_H */

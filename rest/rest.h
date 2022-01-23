#ifndef REST_H
#define REST_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkReply>
#include <QSettings>

class Request : public QObject {
    Q_OBJECT;

public:
    Request(QNetworkRequest *parent = nullptr);
    ~Request();
    static QString base_url;
    QJsonObject response;
    QNetworkReply *net_reply;
    QNetworkRequest *req;
    QString client_id;
    QString user_token;

private slots:
    void read_data();
    void finished_reading();
    void get_settings();

public slots:
    void get(QString url);
    void set_custom_header(QString key, QString value);

signals:
    void finished();

private:
    QByteArray data_buffer;
    QNetworkAccessManager *net_manager;
};

#endif /* REST_H */

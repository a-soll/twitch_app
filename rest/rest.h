#ifndef REST_H
#define REST_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkReply>
#include <QSettings>

class Request : public QObject {
    Q_OBJECT

public:
    Request(QObject *parent = nullptr);
    ~Request();
    static QString base_url;
    QJsonObject response;
    QNetworkReply *net_reply;
    QNetworkRequest *req;
    static QString client_id;
    static QString user_token;

private slots:
    void read_data();
    void finished_reading();

public slots:
    void set_custom_header(QString key, QString value);
    void get(QString url);

signals:
    void finished();

private:
    QByteArray data_buffer;
    QNetworkAccessManager *net_manager;
    static QSettings settings;
};

#endif /* REST_H */

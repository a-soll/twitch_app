#ifndef USER_H
#define USER_H

#include "rest/rest.h"
#include <QObject>

class User : public QObject {
    Q_OBJECT;

public:
    User(QObject *parent = nullptr);

    QString id;
    QString name;

private:
    QString url;
};

#endif /* USER_H */

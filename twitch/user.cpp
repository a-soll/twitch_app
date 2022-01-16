#include "user.h"

User::User(QObject *parent) {
    url = Request::base_url + "/channels";
}

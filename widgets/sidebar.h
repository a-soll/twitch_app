#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QtWidgets/QListView>
#include <QStandardItem>
#include "twitch/user.h"

class SideBar : public QListView {
    Q_OBJECT

public:
    SideBar(QListView *parent = nullptr);
    ~SideBar();
    void add_item();

    QList<QStandardItem*> list_item;
    QStandardItemModel *model;
};

#endif /* SIDEBAR_H */

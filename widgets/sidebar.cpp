#include "sidebar.h"

SideBar::SideBar(QListView *parent) : QListView(parent) {
    model = new QStandardItemModel;
    this->setModel(model);
    this->setMouseTracking(true);
}

SideBar::~SideBar() {
}

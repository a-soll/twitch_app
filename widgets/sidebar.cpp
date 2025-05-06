#include "sidebar.h"

SideBar::SideBar(QListView *parent) : QListView(parent) {
    model = new QStandardItemModel;
    setModel(model);
    this->setMouseTracking(true);
}

SideBar::~SideBar() {
}

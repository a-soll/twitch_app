#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "twitch/user.h"
#include "widgets/secondwidget.h"
#include "widgets/sidebar.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QStringListModel>
#include <QStandardItem>
#include <QListView>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void userName();
    void on_searchButton_clicked();
    void on_searchBar_returnPressed();
    void done();
    void finished_reading();
    void read_data();
    void populate_follow_bar();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *netManager;
    QNetworkRequest *req;
    QNetworkReply *net_reply;
    QByteArray data_buffer;
    QPixmap *img;
    User *appUser;
    Request *request;
    SideBar *sidebar;
};
#endif // MAINWINDOW_H

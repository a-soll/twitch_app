#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "twitch/user.h"
#include "rest/rest.h"
#include "widgets/secondwidget.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>

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

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *netManager;
    QPixmap *img;
    Request *request;
};
#endif // MAINWINDOW_H

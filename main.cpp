#include "widgets/mainwindow.h"

#include <QApplication>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
    QQuickStyle::setStyle("macOS");
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}

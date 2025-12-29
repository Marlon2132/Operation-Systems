#include <QApplication>
#include "todoserver.h"
#include "apiclient.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TodoServer server;
    server.listen(8080);

    ApiClient api;
    api.setBaseUrl("http://127.0.0.1:8080");

    MainWindow w(&api);
    w.show();

    int res = app.exec();

    server.stop();
    return res;
}

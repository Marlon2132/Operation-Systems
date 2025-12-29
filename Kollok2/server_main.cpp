#include <QCoreApplication>
#include "todoserver.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    TodoServer server;
    if (!server.listen(8080)) {
        qWarning() << "Server failed to start";
        return 1;
    }
    qInfo() << "Server running on port 8080";
    return app.exec();
}

#pragma once

#include <QObject>
#include <QHttpServer>
#include "taskstore.h"

class TodoServer : public QObject {
    Q_OBJECT
public:
    explicit TodoServer(QObject *parent = nullptr);
    bool listen(quint16 port = 8080);
    void stop();

private:
    QHttpServer m_server;
    TaskStore m_store;
    void setupRoutes();
};

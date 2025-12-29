#pragma once

#include <QObject>
#include <memory>
#include <thread>
#include <atomic>
#include "taskstore.h"

#include "httplib.h"

class TodoServer : public QObject {
    Q_OBJECT
public:
    explicit TodoServer(QObject *parent = nullptr);
    ~TodoServer() override;
    bool listen(quint16 port = 8080);
    void stop();

private:
    void setupRoutes();
    TaskStore m_store;
    std::unique_ptr<httplib::Server> m_server;
    std::thread m_thread;
    std::atomic<bool> m_running{false};
    quint16 m_port = 8080;
};

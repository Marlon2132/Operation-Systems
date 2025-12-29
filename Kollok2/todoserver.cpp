#include "todoserver.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QDebug>

#include <functional>

using namespace httplib;

TodoServer::TodoServer(QObject *parent)
    : QObject(parent),
    m_server(std::make_unique<Server>())
{

}

TodoServer::~TodoServer()
{
    stop();
}

bool TodoServer::listen(quint16 port)
{
    if (m_running.load()) return false;
    m_port = port;

    setupRoutes();

    m_running.store(true);

    m_thread = std::thread([this]() {
        qInfo() << "Starting HTTP server on port" << m_port;
        if (!m_server->listen("0.0.0.0", static_cast<int>(m_port))) {
            qWarning() << "httplib server failed to start on port" << m_port;
        }
        m_running.store(false);
    });

    return true;
}

void TodoServer::stop()
{
    if (!m_running.load()) {
        if (m_thread.joinable()) {
            m_thread.join();
        }
        return;
    }

    if (m_server) {
        m_server->stop();
    }

    if (m_thread.joinable()) {
        m_thread.join();
    }
    m_running.store(false);
    qInfo() << "HTTP server stopped";
}

void TodoServer::setupRoutes()
{
    // GET /tasks
    m_server->Get("/tasks", [this](const Request &req, Response &res) {
        QJsonArray arr;
        for (const Task &t : m_store.all()) {
            arr.append(t.toJson());
        }
        QJsonDocument doc(arr);
        QByteArray bytes = doc.toJson(QJsonDocument::Compact);
        res.set_content(std::string(bytes.constData(), bytes.size()), "application/json");
        res.status = 200;
    });

    // POST /tasks
    m_server->Post("/tasks", [this](const Request &req, Response &res) {
        QByteArray body(req.body.c_str(), static_cast<int>(req.body.size()));
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(body, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            QJsonObject e; e["error"] = "invalid json";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 400;
            return;
        }
        Task t = Task::fromJson(doc.object());
        Task created = m_store.create(t);
        QJsonDocument out(created.toJson());
        QByteArray ob = out.toJson(QJsonDocument::Compact);
        res.set_content(std::string(ob.constData(), ob.size()), "application/json");
        res.status = 201;
    });


    // GET /tasks/{id}
    m_server->Get(R"(/tasks/(\d+))", [this](const Request &req, Response &res) {
        if (req.matches.size() < 2) {
            res.status = 404;
            return;
        }
        int id = std::stoi(req.matches[1]);
        auto opt = m_store.get(id);
        if (!opt) {
            QJsonObject e; e["error"] = "not found";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 404;
            return;
        }
        QJsonDocument out(opt->toJson());
        QByteArray ob = out.toJson(QJsonDocument::Compact);
        res.set_content(std::string(ob.constData(), ob.size()), "application/json");
        res.status = 200;
    });

    // PUT /tasks/{id}
    m_server->Put(R"(/tasks/(\d+))", [this](const Request &req, Response &res) {
        if (req.matches.size() < 2) {
            res.status = 404;
            return;
        }
        int id = std::stoi(req.matches[1]);
        QByteArray body(req.body.c_str(), static_cast<int>(req.body.size()));
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(body, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            QJsonObject e; e["error"] = "invalid json";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 400;
            return;
        }
        Task t = Task::fromJson(doc.object());
        auto resTask = m_store.replace(id, t);
        if (!resTask) {
            QJsonObject e; e["error"] = "not found";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 404;
            return;
        }
        QJsonDocument out(resTask->toJson());
        QByteArray ob = out.toJson(QJsonDocument::Compact);
        res.set_content(std::string(ob.constData(), ob.size()), "application/json");
        res.status = 200;
    });

    // PATCH /tasks/{id}
    m_server->Patch(R"(/tasks/(\d+))", [this](const Request &req, Response &res) {
        if (req.matches.size() < 2) {
            res.status = 404;
            return;
        }
        int id = std::stoi(req.matches[1]);
        QByteArray body(req.body.c_str(), static_cast<int>(req.body.size()));
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(body, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            QJsonObject e; e["error"] = "invalid json";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 400;
            return;
        }
        auto resTask = m_store.patch(id, doc.object());
        if (!resTask) {
            QJsonObject e; e["error"] = "not found";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 404;
            return;
        }
        QJsonDocument out(resTask->toJson());
        QByteArray ob = out.toJson(QJsonDocument::Compact);
        res.set_content(std::string(ob.constData(), ob.size()), "application/json");
        res.status = 200;
    });

    // DELETE /tasks/{id}
    m_server->Delete(R"(/tasks/(\d+))", [this](const Request &req, Response &res) {
        if (req.matches.size() < 2) {
            res.status = 404;
            return;
        }
        int id = std::stoi(req.matches[1]);
        if (!m_store.remove(id)) {
            QJsonObject e; e["error"] = "not found";
            QJsonDocument ed(e);
            QByteArray eb = ed.toJson(QJsonDocument::Compact);
            res.set_content(std::string(eb.constData(), eb.size()), "application/json");
            res.status = 404;
            return;
        }
        QJsonObject ok; ok["result"] = "deleted";
        QJsonDocument od(ok);
        QByteArray ob = od.toJson(QJsonDocument::Compact);
        res.set_content(std::string(ob.constData(), ob.size()), "application/json");
        res.status = 200;
    });

    m_server->Get("/health", [](const Request &, Response &res) {
        res.set_content("ok", "text/plain");
        res.status = 200;
    });
}

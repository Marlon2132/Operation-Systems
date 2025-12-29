#include "todoserver.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QRegularExpression>
#include <QHttpServerResponse>
#include <QHttpServerRequest>
#include <QHostAddress>

TodoServer::TodoServer(QObject *parent) : QObject(parent) {
    setupRoutes();
}

void TodoServer::setupRoutes() {
    // GET /tasks
    m_server.route("/tasks", QHttpServerRequest::Method::Get, [this]() {
        QJsonArray arr;
        for (const Task &t : m_store.all()) {
            arr.append(t.toJson());
        }
        return QHttpServerResponse::fromJson(arr);
    });

    // POST /tasks
    m_server.route("/tasks", QHttpServerRequest::Method::Post, [this](const QHttpServerRequest &req) {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(req.body(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            return QHttpServerResponse(400, "application/json", QJsonDocument(QJsonObject{{"error","invalid json"}}).toJson());
        }
        Task t = Task::fromJson(doc.object());
        Task created = m_store.create(t);
        QHttpServerResponse resp = QHttpServerResponse::fromJson(created.toJson());
        resp.setStatusCode(201);
        return resp;
    });

    QRegularExpression re("^/tasks/(\\d+)$");

    // GET /tasks/{id}
    m_server.route(re, QHttpServerRequest::Method::Get, [this](const QHttpServerRequest &req) {
        auto match = req.path().match(QRegularExpression("^/tasks/(\\d+)$"));
        int id = match.captured(1).toInt();
        auto opt = m_store.get(id);
        if (!opt) return QHttpServerResponse(404, "application/json", QJsonDocument(QJsonObject{{"error","not found"}}).toJson());
        return QHttpServerResponse::fromJson(opt->toJson());
    });

    // PUT /tasks/{id}
    m_server.route(re, QHttpServerRequest::Method::Put, [this](const QHttpServerRequest &req) {
        auto match = req.path().match(QRegularExpression("^/tasks/(\\d+)$"));
        int id = match.captured(1).toInt();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(req.body(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            return QHttpServerResponse(400, "application/json", QJsonDocument(QJsonObject{{"error","invalid json"}}).toJson());
        }
        Task t = Task::fromJson(doc.object());
        auto res = m_store.replace(id, t);
        if (!res) return QHttpServerResponse(404, "application/json", QJsonDocument(QJsonObject{{"error","not found"}}).toJson());
        return QHttpServerResponse::fromJson(res->toJson());
    });

    // PATCH /tasks/{id}
    m_server.route(re, QHttpServerRequest::Method::Patch, [this](const QHttpServerRequest &req) {
        auto match = req.path().match(QRegularExpression("^/tasks/(\\d+)$"));
        int id = match.captured(1).toInt();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(req.body(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            return QHttpServerResponse(400, "application/json", QJsonDocument(QJsonObject{{"error","invalid json"}}).toJson());
        }
        auto res = m_store.patch(id, doc.object());
        if (!res) return QHttpServerResponse(404, "application/json", QJsonDocument(QJsonObject{{"error","not found"}}).toJson());
        return QHttpServerResponse::fromJson(res->toJson());
    });

    // DELETE /tasks/{id}
    m_server.route(re, QHttpServerRequest::Method::Delete, [this](const QHttpServerRequest &req) {
        auto match = req.path().match(QRegularExpression("^/tasks/(\\d+)$"));
        int id = match.captured(1).toInt();
        if (!m_store.remove(id)) return QHttpServerResponse(404, "application/json", QJsonDocument(QJsonObject{{"error","not found"}}).toJson());
        return QHttpServerResponse(200, "application/json", QJsonDocument(QJsonObject{{"result","deleted"}}).toJson());
    });
}

bool TodoServer::listen(quint16 port) {
    return m_server.listen(QHostAddress::Any, port);
}

void TodoServer::stop() {
    m_server.close();
}

#include "apiclient.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

ApiClient::ApiClient(QObject *parent)
    : QObject(parent),
    m_net(new QNetworkAccessManager(this)),
    m_base("http://127.0.0.1:8080")
{
}

void ApiClient::setBaseUrl(const QString &url) {
    m_base = url;
}


void ApiClient::handleReply(QNetworkReply *reply, std::function<void(QByteArray,int)> cb) {
    QByteArray data = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (cb) cb(data, code);
    reply->deleteLater();
}

void ApiClient::getTasks(std::function<void(QByteArray,int)> cb) {
    QNetworkRequest req(QUrl(m_base + "/tasks"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *r = m_net->get(req);
    connect(r, &QNetworkReply::finished, [this,r,cb]{ handleReply(r, cb); });
}

void ApiClient::createTask(const QJsonObject &obj, std::function<void(QByteArray,int)> cb) {
    QNetworkRequest req(QUrl(m_base + "/tasks"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *r = m_net->post(req, QJsonDocument(obj).toJson());
    connect(r, &QNetworkReply::finished, [this,r,cb]{ handleReply(r, cb); });
}

void ApiClient::putTask(int id, const QJsonObject &obj, std::function<void(QByteArray,int)> cb) {
    QNetworkRequest req(QUrl(m_base + QString("/tasks/%1").arg(id)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *r = m_net->sendCustomRequest(req, "PUT", QJsonDocument(obj).toJson());
    connect(r, &QNetworkReply::finished, [this,r,cb]{ handleReply(r, cb); });
}

void ApiClient::patchTask(int id, const QJsonObject &obj, std::function<void(QByteArray,int)> cb) {
    QNetworkRequest req(QUrl(m_base + QString("/tasks/%1").arg(id)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *r = m_net->sendCustomRequest(req, "PATCH", QJsonDocument(obj).toJson());
    connect(r, &QNetworkReply::finished, [this,r,cb]{ handleReply(r, cb); });
}

void ApiClient::deleteTask(int id, std::function<void(QByteArray,int)> cb) {
    QNetworkRequest req(QUrl(m_base + QString("/tasks/%1").arg(id)));
    QNetworkReply *r = m_net->deleteResource(req);
    connect(r, &QNetworkReply::finished, [this,r,cb]{ handleReply(r, cb); });
}

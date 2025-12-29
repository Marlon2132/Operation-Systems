#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <functional>

class ApiClient : public QObject {
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = nullptr);

    void setBaseUrl(const QString &url) { m_base = url; }

    void getTasks(std::function<void(QByteArray,int)> cb);
    void createTask(const QJsonObject &obj, std::function<void(QByteArray,int)> cb);
    void putTask(int id, const QJsonObject &obj, std::function<void(QByteArray,int)> cb);
    void patchTask(int id, const QJsonObject &obj, std::function<void(QByteArray,int)> cb);
    void deleteTask(int id, std::function<void(QByteArray,int)> cb);

private:
    QNetworkAccessManager *m_net;
    QString m_base;
    void handleReply(QNetworkReply *reply, std::function<void(QByteArray,int)> cb);
};

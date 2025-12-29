#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <functional>

class ApiClient : public QObject {
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = nullptr);

    void setBaseUrl(const QString &url);
    void getTasks(std::function<void(QByteArray,int)> cb);
    void createTask(const QJsonObject &obj, std::function<void(QByteArray,int)> cb);
    void putTask(int id, const QJsonObject &obj, std::function<void(QByteArray,int)> cb);
    void patchTask(int id, const QJsonObject &obj, std::function<void(QByteArray,int)> cb);
    void deleteTask(int id, std::function<void(QByteArray,int)> cb);

private:
    QNetworkAccessManager *m_net = nullptr;
    QString m_base;
    void handleReply(QNetworkReply *reply, std::function<void(QByteArray,int)> cb);
};

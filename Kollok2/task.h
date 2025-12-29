#pragma once

#include <QString>
#include <QJsonObject>
#include <QMetaType>

class Task {
public:
    Task() = default;
    explicit Task(int id, QString title = {}, QString description = {}, QString status = {});

    int id() const noexcept;
    QString title() const;
    QString description() const;
    QString status() const;

    void setId(int id) noexcept;
    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setStatus(const QString &status);

    QJsonObject toJson() const;
    static Task fromJson(const QJsonObject &o);

private:
    int m_id = 0;
    QString m_title;
    QString m_description;
    QString m_status;
};

Q_DECLARE_METATYPE(Task)

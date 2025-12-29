#include "task.h"

Task::Task(int id, QString title, QString description, QString status)
    : m_id(id), m_title(std::move(title)), m_description(std::move(description)), m_status(std::move(status))
{}

int Task::id() const noexcept { return m_id; }
QString Task::title() const { return m_title; }
QString Task::description() const { return m_description; }
QString Task::status() const { return m_status; }

void Task::setId(int id) noexcept { m_id = id; }

void Task::setTitle(const QString &title) {
    m_title = title.trimmed();
}

void Task::setDescription(const QString &description) {
    m_description = description;
}

void Task::setStatus(const QString &status) {
    if (status == "todo" || status == "in_progress" || status == "done") {
        m_status = status;
    } else {
        m_status = "todo";
    }
}

QJsonObject Task::toJson() const {
    QJsonObject o;
    o["id"] = m_id;
    o["title"] = m_title;
    o["description"] = m_description;
    o["status"] = m_status;

    return o;
}

Task Task::fromJson(const QJsonObject &o) {
    Task t;

    if (o.contains("id")) t.setId(o["id"].toInt());
    if (o.contains("title")) t.setTitle(o["title"].toString());
    if (o.contains("description")) t.setDescription(o["description"].toString());
    if (o.contains("status")) t.setStatus(o["status"].toString());

    return t;
}

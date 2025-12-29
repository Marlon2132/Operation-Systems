#pragma once

#include <QObject>
#include <QMap>
#include <QList>
#include <optional>
#include "task.h"

class TaskStore : public QObject {
    Q_OBJECT
public:
    explicit TaskStore(QObject *parent = nullptr);

    QList<Task> all() const;
    Task create(const Task &t);
    std::optional<Task> get(int id) const;
    bool remove(int id);
    std::optional<Task> replace(int id, const Task &t);
    std::optional<Task> patch(int id, const QJsonObject &patch);

    int nextId() const noexcept;
    void setNextId(int id) noexcept;

signals:
    void taskCreated(const Task &t);
    void taskUpdated(const Task &t);
    void taskDeleted(int id);

private:
    QMap<int, Task> m_tasks;
    int m_nextId = 1;

    Task makeWithId(const Task &t, int id) const;
};

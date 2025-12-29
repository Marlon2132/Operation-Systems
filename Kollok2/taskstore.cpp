#include "taskstore.h"

TaskStore::TaskStore(QObject *parent) : QObject(parent) {
    Task t;
    t.setTitle("Пример: купить молоко");
    t.setDescription("3.2%");
    t.setStatus("todo");
    create(t);
}

QList<Task> TaskStore::all() const {
    return m_tasks.values();
}

Task TaskStore::makeWithId(const Task &t, int id) const {
    Task copy = t;
    copy.setId(id);
    if (copy.status().isEmpty()) copy.setStatus("todo");

    return copy;
}

Task TaskStore::create(const Task &t) {
    Task copy = makeWithId(t, m_nextId++);
    m_tasks.insert(copy.id(), copy);
    emit taskCreated(copy);

    return copy;
}

std::optional<Task> TaskStore::get(int id) const {
    if (!m_tasks.contains(id)) return std::nullopt;

    return m_tasks.value(id);
}

bool TaskStore::remove(int id) {
    if (!m_tasks.contains(id)) return false;
    m_tasks.remove(id);
    emit taskDeleted(id);

    return true;
}

std::optional<Task> TaskStore::replace(int id, const Task &t) {
    if (!m_tasks.contains(id)) return std::nullopt;
    Task copy = makeWithId(t, id);
    m_tasks[id] = copy;
    emit taskUpdated(copy);

    return copy;
}

std::optional<Task> TaskStore::patch(int id, const QJsonObject &patch) {
    if (!m_tasks.contains(id)) return std::nullopt;
    Task cur = m_tasks[id];
    if (patch.contains("title")) cur.setTitle(patch["title"].toString());
    if (patch.contains("description")) cur.setDescription(patch["description"].toString());
    if (patch.contains("status")) cur.setStatus(patch["status"].toString());
    m_tasks[id] = cur;
    emit taskUpdated(cur);

    return cur;
}

int TaskStore::nextId() const noexcept {
    return m_nextId;
}

void TaskStore::setNextId(int id) noexcept {
    m_nextId = id;
}

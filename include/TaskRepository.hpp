#pragma once

#include <vector>
#include <QObject>
#include <QSqlDatabase>

struct Task;

class TaskRepository
    : public QObject
{
    Q_OBJECT

public:
    explicit TaskRepository(QObject* parent = nullptr);
    
    ~TaskRepository();

    [[nodiscard]] auto getAllTasks() const -> std::vector<Task>;

    [[nodiscard]] auto getAllStatuses() const -> std::vector<QString>;

    auto insertTask(const QString& status,
                    const QString& description) const -> void;

    auto deleteTask(const QString& description) const -> void;

    auto moveTaskTo(const QString& description,
                    const QString& newStatus) const -> void;

private:
    QSqlDatabase m_DbConn;
};
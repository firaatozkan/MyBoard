#pragma once

#include <vector>
#include <QSqlDatabase>

struct Task;

class TaskRepository
{
private:
    TaskRepository();

public:
    ~TaskRepository();
    static TaskRepository& get();
    std::vector<Task> getAllTasks() const;
    std::vector<QString> getAllStatuses() const;

private:
    QSqlDatabase m_DbConn;
};
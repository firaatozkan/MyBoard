#include "Task.hpp"
#include <QVariant>
#include <QSqlQuery>
#include "TaskRepository.hpp"

TaskRepository::TaskRepository()
    : m_DbConn(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_DbConn.setDatabaseName(DB_PATH_ENV);
    m_DbConn.open();

    QSqlQuery createQuery;

    createQuery.exec("create table if not exists tasks"
                     "(id integer primary key autoincrement, "
                     "status text, "
                     "description text)");
}

TaskRepository::~TaskRepository()
{
    m_DbConn.close();
}

TaskRepository& TaskRepository::get()
{
    static TaskRepository instance;
    return instance;
}

std::vector<Task> TaskRepository::getAllTasks() const
{
    std::vector<Task> output;

    QSqlQuery selectStatuses;

    if (selectStatuses.exec("select * from tasks"))
    {
        while (selectStatuses.next())
        {
            output.emplace_back(selectStatuses
                                    .value(1)
                                    .toString(),
                                selectStatuses
                                    .value(2)
                                    .toString());
        }
    }

    return output;
}

std::vector<QString> TaskRepository::getAllStatuses() const
{
    std::vector<QString> output;

    QSqlQuery selectStatuses;

    if (selectStatuses.exec("select status from tasks"))
    {
        while (selectStatuses.next())
            output.emplace_back(selectStatuses
                                    .value(0)
                                    .toString());
    }

    return output;
}

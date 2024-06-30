#include "Task.hpp"
#include <QDebug>
#include <QVariant>
#include <QSqlQuery>
#include "TaskRepository.hpp"


TaskRepository::TaskRepository(QObject* parent)
    : QObject(parent),
      m_DbConn(QSqlDatabase::addDatabase("QSQLITE"))
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
    QSqlQuery cleanOnClose;
    cleanOnClose.exec("delete from tasks where status = 'Closed'");
    m_DbConn.close();
}


[[nodiscard]]
auto TaskRepository::getAllTasks() const -> std::vector<Task>
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


[[nodiscard]]
auto TaskRepository::getAllStatuses() const -> std::vector<QString>
{
    std::vector<QString> output;

    QSqlQuery selectStatuses;

    if (selectStatuses.exec("select distinct status from tasks order by status"))
    {
        while (selectStatuses.next())
            output.emplace_back(selectStatuses
                                    .value(0)
                                    .toString());
    }

    return output;
}


auto TaskRepository::insertTask(const QString& status,
                                const QString& description) const -> void
{
    QSqlQuery insertQuery;
    insertQuery.prepare("insert into tasks (status, description) values (:status, :description)");
    insertQuery.bindValue(":status", status);
    insertQuery.bindValue(":description", description);
    insertQuery.exec();
}


auto TaskRepository::deleteTask(const QString& description) const -> void
{
    QSqlQuery deleteQuery;

    deleteQuery.prepare("delete from tasks where description = :description");

    deleteQuery.bindValue(":description", description);
    deleteQuery.exec();
}


auto TaskRepository::moveTaskTo(const QString& description,
                                const QString& newStatus) const -> void
{
    QSqlQuery modifyQuery;

    modifyQuery.prepare("update tasks set status = :newStatus where description = :description");

    modifyQuery.bindValue(":newStatus", newStatus);
    modifyQuery.bindValue(":description", description);

    modifyQuery.exec();
}
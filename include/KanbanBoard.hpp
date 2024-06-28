#pragma once

#include <vector>
#include <QMainWindow>
#include <unordered_map>

class QWidget;
class QHBoxLayout;
class QListWidget;
class QListWidgetItem;

class KanbanBoard
    : public QMainWindow
{
    Q_OBJECT

    using StatusWidgetMap = std::unordered_map<QString,
                                               QListWidget *>;

public:
    explicit KanbanBoard(QWidget *parent = nullptr);
    ~KanbanBoard() = default;

private slots:
    void taskClicked(QListWidgetItem *const task);
    void addButtonClicked();
    void removeButtonClicked();

private:
    void addStatuses(QHBoxLayout *const layout);
    void addButtons(QHBoxLayout *const layout);
    void fillTaskLists();

private:
    QWidget *m_CentralWidget;
    StatusWidgetMap m_StatusWidgetMap;
    QListWidgetItem *m_CurrentActivatedTask{nullptr};
};
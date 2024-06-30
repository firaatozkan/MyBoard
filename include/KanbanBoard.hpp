#pragma once

#include <QMainWindow>
#include <unordered_map>
#include "TaskRepository.hpp"

class QWidget;
class QHBoxLayout;
class QListWidget;
class QListWidgetItem;

class KanbanBoard
    : public QMainWindow
{
    Q_OBJECT

    using StatusWidgetMap = std::unordered_map<QString,
                                               std::reference_wrapper<QListWidget>>;

    using OptionalListWidgetItemRef = std::optional<std::reference_wrapper<QListWidgetItem>>;

public:
    static constexpr std::string_view statuses[] = {"Backlog",
                                                    "In Progress",
                                                    "Ready for Verification",
                                                    "Closed"};

public:
    explicit KanbanBoard(QWidget* parent = nullptr);

    ~KanbanBoard() = default;

    auto initWindow() -> void;

    [[nodiscard]] auto getTaskRepository() const -> const TaskRepository&;

private:
    auto addStatuses(QHBoxLayout& mainLayout) -> void;

    auto addButtons(QHBoxLayout& mainLayout) -> void;

    auto fillTaskLists() -> void;

private:
    TaskRepository m_TaskRepository;
    StatusWidgetMap m_StatusWidgetMap;
    std::unique_ptr<QWidget> m_CentralWidget {nullptr};
    OptionalListWidgetItemRef m_CurrentActivatedTask {std::nullopt};
};
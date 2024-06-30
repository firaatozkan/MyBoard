#include <ranges>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QWidget>
#include "Task.hpp"
#include <functional>
#include <QListWidget>
#include <QPushButton>
#include <string_view>
#include "Utility.hpp"
#include "KanbanBoard.hpp"
#include "TaskMovingDialog.hpp"
#include "TaskAdditionDialog.hpp"


KanbanBoard::KanbanBoard(QWidget* parent)
    : QMainWindow(parent),
      m_TaskRepository(this)
{
    this->initWindow();
}


auto KanbanBoard::initWindow() -> void
{
    this->m_CentralWidget.reset(new QWidget);

    this->setCentralWidget(m_CentralWidget.get());

    auto mainLayout = new QHBoxLayout;

    this->addStatuses(*mainLayout);

    this->addButtons(*mainLayout);

    this->fillTaskLists();

    m_CentralWidget->setLayout(mainLayout);
}


auto KanbanBoard::addStatuses(QHBoxLayout& mainLayout) -> void
{
    std::ranges::transform(statuses,
                           Utility::QLayoutInserter(&mainLayout),
                           [this] (const auto status)
                           {
                               const auto layout    = new QVBoxLayout;
                               const auto label     = new QLabel(status.data(), this);
                               const auto list      = new QListWidget(this);

                               layout->addWidget(label, 0, Qt::AlignCenter);
                               layout->addWidget(list);

                               QObject::connect(list,
                                                &QListWidget::itemClicked,
                                                [this] (const auto task)
                                                {
                                                    m_CurrentActivatedTask = task ? OptionalListWidgetItemRef(*task)
                                                                                  : std::nullopt;
                                                });

                               m_StatusWidgetMap.insert_or_assign(status.data(),
                                                                  *list);

                               return layout;
                           });
}


auto KanbanBoard::addButtons(QHBoxLayout& mainLayout) -> void
{
    const auto buttonLayout = new QVBoxLayout;
    const auto addButton    = new QPushButton("Add Task", this);
    const auto moveButton   = new QPushButton("Move Task", this);
    const auto removeButton = new QPushButton("Remove Task", this);

    QObject::connect(addButton,
                     &QPushButton::clicked,
                     [this]
                     {
                         TaskAdditionDialog task(this);
                         task.setFixedSize(600, 400);
                         task.exec();
                     });

    QObject::connect(moveButton,
                     &QPushButton::clicked,
                     [this]
                     {
                         if (not m_CurrentActivatedTask)
                             return;

                         TaskMovingDialog task(*m_CurrentActivatedTask,
                                               this);

                         task.setFixedSize(600, 400);
                         task.exec();
                     });

    QObject::connect(removeButton,
                     &QPushButton::clicked,
                     [this]
                     {
                         if (not m_CurrentActivatedTask)
                             return;

                         const QListWidgetItem& task = *m_CurrentActivatedTask;

                         m_TaskRepository.deleteTask(task.text());
                         m_CurrentActivatedTask = std::nullopt;
                         this->initWindow();
                     });

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(moveButton);
    buttonLayout->addWidget(removeButton);

    mainLayout.addLayout(buttonLayout);
}


auto KanbanBoard::fillTaskLists() -> void
{
    auto tasks = m_TaskRepository.getAllTasks();

    std::ranges::for_each(tasks | std::views::as_rvalue,
                          [this] (auto&& task)
                          {
                              QListWidget& statusWidget = m_StatusWidgetMap.at(std::move(task.status));

                              statusWidget.addItem(std::move(task.description));
                          });
}


[[nodiscard]]
auto KanbanBoard::getTaskRepository() const -> const TaskRepository&
{
    return m_TaskRepository;
}
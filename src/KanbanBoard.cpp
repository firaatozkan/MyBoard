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
#include "TaskDialog.hpp"
#include "KanbanBoard.hpp"
#include "TaskRepository.hpp"

KanbanBoard::KanbanBoard(QWidget *parent)
    : QMainWindow(parent),
      m_CentralWidget(new QWidget(this))
{
    this->setCentralWidget(m_CentralWidget);

    auto mainLayout = new QHBoxLayout;

    this->addStatuses(mainLayout);

    this->addButtons(mainLayout);

    this->fillTaskLists();

    m_CentralWidget->setLayout(mainLayout);
}

void KanbanBoard::addStatuses(QHBoxLayout *const layout)
{
    auto statuses = TaskRepository::get()
                        .getAllStatuses();

    for (auto&& status : statuses |
                             std::views::as_rvalue)
    {
        auto temp   = new QVBoxLayout;
        auto label  = new QLabel(status, this);
        auto list   = new QListWidget(this);

        temp->addWidget(label, 0, Qt::AlignCenter);
        temp->addWidget(list);

        connect(list,
                &QListWidget::itemClicked,
                this,
                &KanbanBoard::taskClicked);

        m_StatusWidgetMap.emplace(std::move(status),
                                  list);

        layout->addLayout(temp);
    }
}

void KanbanBoard::addButtons(QHBoxLayout *const layout)
{
    auto buttonLayout   = new QVBoxLayout;
    auto addButton      = new QPushButton("Add Task", this);
    auto removeButton   = new QPushButton("Remove Task", this);

    connect(addButton,
            &QPushButton::clicked,
            this,
            &KanbanBoard::addButtonClicked);

    connect(removeButton,
            &QPushButton::clicked,
            this,
            &KanbanBoard::removeButtonClicked);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    
    layout->addLayout(buttonLayout);
}

void KanbanBoard::fillTaskLists()
{
    auto tasks = TaskRepository::get()
                     .getAllTasks();

    for (auto&& task : tasks |
                           std::views::as_rvalue)
    {
        m_StatusWidgetMap[task.status]->addItem(
            std::move(task.description));
    }
}

void KanbanBoard::taskClicked(QListWidgetItem *const task)
{
    m_CurrentActivatedTask = task;
}

void KanbanBoard::addButtonClicked()
{
    TaskDialog task(this);
    task.setFixedSize(600, 400);
    task.exec();
}

void KanbanBoard::removeButtonClicked()
{
    qDebug() << "remove";
}
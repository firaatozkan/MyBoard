#include <ranges>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "Utility.hpp"
#include "KanbanBoard.hpp"
#include "TaskRepository.hpp"
#include "TaskAdditionDialog.hpp"


TaskAdditionDialog::TaskAdditionDialog(QWidget* parent)
    : QDialog(parent),
      m_TaskEdit(new QLineEdit(this)),
      m_StatusBox(new QComboBox(this))
{
    auto centralLayout = new QVBoxLayout;

    std::ranges::transform(KanbanBoard::statuses,
                           Utility::QStringInserter(m_StatusBox),
                           [] (const auto status)
                           {
                               return status.data();
                           });

    m_StatusBox->setCurrentIndex(-1);

    auto addButton = new QPushButton("Add Task", this);

    centralLayout->addWidget(new QLabel("Task description", this),
                             0,
                             Qt::AlignCenter);

    centralLayout->addWidget(m_TaskEdit,
                             0,
                             Qt::AlignCenter);

    centralLayout->addWidget(new QLabel("Status", this),
                             0,
                             Qt::AlignCenter);

    centralLayout->addWidget(m_StatusBox,
                             0,
                             Qt::AlignCenter);

    centralLayout->addWidget(addButton,
                             0,
                             Qt::AlignCenter);

    QObject::connect(addButton,
                     &QPushButton::clicked,
                     [this]
                     {
                         if (m_StatusBox->currentIndex() != -1 &&
                             not m_TaskEdit->text().isEmpty())
                         {
                             auto& kanbanBoard = reinterpret_cast<KanbanBoard&>(*this->parent());

                             kanbanBoard.getTaskRepository().insertTask(
                                 m_StatusBox->currentText(),
                                 m_TaskEdit->text());

                             kanbanBoard.initWindow();

                             this->close();
                         }
                     });

    this->setLayout(centralLayout);
}
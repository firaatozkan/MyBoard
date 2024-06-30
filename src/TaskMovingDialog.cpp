#include <ranges>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "Utility.hpp"
#include "KanbanBoard.hpp"
#include <QListWidgetItem>
#include "TaskRepository.hpp"
#include "TaskMovingDialog.hpp"


TaskMovingDialog::TaskMovingDialog(QListWidgetItem& selectedTask,
                                   QWidget* parent)
    : QDialog(parent),
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

    auto moveButton = new QPushButton("Move Task", this);

    centralLayout->addWidget(new QLabel("Status", this),
                             0,
                             Qt::AlignCenter);

    centralLayout->addWidget(m_StatusBox,
                             0,
                             Qt::AlignCenter);

    centralLayout->addWidget(moveButton,
                             0,
                             Qt::AlignCenter);

    QObject::connect(moveButton,
                     &QPushButton::clicked,
                     [this, &selectedTask]
                     {
                         if (m_StatusBox->currentIndex() != -1)
                         {
                             auto& kanbanBoard = reinterpret_cast<KanbanBoard&>(*this->parent());

                             kanbanBoard.getTaskRepository().moveTaskTo(selectedTask.text(),
                                                                        m_StatusBox->currentText());

                             kanbanBoard.initWindow();

                             this->close();
                         }
                     });

    this->setLayout(centralLayout);
}
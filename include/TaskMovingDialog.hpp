#pragma once

#include <QDialog>

class QComboBox;
class QLineEdit;
class QListWidgetItem;

class TaskMovingDialog
    : public QDialog
{
    Q_OBJECT

public:
    TaskMovingDialog(QListWidgetItem& selectedTask,
                     QWidget* parent = nullptr);

    ~TaskMovingDialog() noexcept = default;

private:
    QComboBox* m_StatusBox;
};
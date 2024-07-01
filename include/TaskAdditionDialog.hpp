#pragma once

#include <QDialog>

class QComboBox;
class QLineEdit;

class TaskAdditionDialog
    : public QDialog
{
    Q_OBJECT

public:
    explicit TaskAdditionDialog(QWidget* parent = nullptr);
    
    ~TaskAdditionDialog() noexcept = default;

private:
    QLineEdit* m_TaskEdit;
    QComboBox* m_StatusBox;
};
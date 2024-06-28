#pragma once

#include <QDialog>

class TaskDialog
    : public QDialog
{
    Q_OBJECT
    
public:
    explicit TaskDialog(QWidget* parent = nullptr);
    ~TaskDialog() = default;
};
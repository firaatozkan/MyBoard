#include <QVBoxLayout>
#include "TaskDialog.hpp"

TaskDialog::TaskDialog(QWidget* parent)
    : QDialog(parent)
{
    auto centralLayout = new QVBoxLayout;
    setLayout(centralLayout);
}

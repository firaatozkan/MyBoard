#pragma once

#include <QString>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <type_traits>

namespace Utility
{
    struct QLayoutInserter
    {
        QHBoxLayout* layoutRef;
        QVBoxLayout* childLayout {nullptr};

        using difference_type = std::ptrdiff_t;

        [[nodiscard]] auto operator*() -> QVBoxLayout*&
        {
            return childLayout;
        }

        [[nodiscard]] auto operator++() -> QLayoutInserter&
        {
            if (childLayout)
            {
                layoutRef->addLayout(childLayout);
                childLayout = nullptr;
            }
            return *this;
        }

        [[nodiscard]] auto operator++(int) const -> QLayoutInserter
        {
            return *this;
        }
    };

    struct QStringInserter
    {
        QComboBox*  comboBoxRef;
        QString     string;

        using difference_type = std::ptrdiff_t;

        [[nodiscard]] auto operator*() -> QString&
        {
            return string;
        }

        [[nodiscard]] auto operator++() -> QStringInserter&
        {
            comboBoxRef->addItem(string);
            return *this;
        }

        [[nodiscard]] auto operator++(int) const -> QStringInserter
        {
            return *this;
        }
    };
}
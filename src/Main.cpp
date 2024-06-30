#include <QApplication>
#include "KanbanBoard.hpp"

auto main(int argc, char** argv) -> int
{
    QApplication app(argc, argv);

    KanbanBoard board;
    board.resize(1280, 720);
    board.show();

    return app.exec();
}
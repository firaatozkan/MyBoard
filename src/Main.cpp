#include <QApplication>
#include "KanbanBoard.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    KanbanBoard board;
    board.resize(1280, 720);
    board.show();

    return app.exec();
}
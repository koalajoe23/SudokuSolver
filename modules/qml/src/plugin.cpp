#include <sudokusolver/qml/plugin.hpp>
#include <sudokusolver/qml/board.hpp>
#include <sudokusolver/qml/cell.hpp>


#include <qqml.h>

using namespace SudokuSolver;

void Qml::Plugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String("SudokuSolver"));
    qmlRegisterType<Qml::Board>(uri, 1, 0, "BoardModel");
    qmlRegisterUncreatableType<Qml::Cell>(uri, 1, 0, "CellModel", "Cells cannot be instantiated!");
}

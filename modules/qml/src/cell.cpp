#include <sudokusolver/qml/cell.hpp>

using namespace SudokuSolver;

Qml::Cell::Cell()
    : QObject(nullptr)
    , _cell(new SudokuSolver::Core::Cell())
    , _cleanupCell(true)
{

}

Qml::Cell::Cell(QObject* parent)
    : QObject(parent)
    , _cell(new SudokuSolver::Core::Cell())
    , _cleanupCell(true)
{

}

Qml::Cell::Cell(Core::Cell& cell)
    : QObject(nullptr)
    , _cell(&cell)
    , _cleanupCell(false)
{

}

Qml::Cell::~Cell()
{
    if(_cleanupCell && _cell != nullptr)
    {
        delete(_cell);
    }
    _cell = nullptr;
}

#ifndef SUDOKUSOLVER_QML_CELL_HPP_INCLUDED
#define SUDOKUSOLVER_QML_CELL_HPP_INCLUDED

#include <sudokusolver/core/board.hpp>

#include <QObject>

namespace SudokuSolver { namespace Qml {

class Cell : public QObject {
    Q_OBJECT
public:
    Cell();
    Cell(QObject* parent);
    Cell(SudokuSolver::Core::Cell& cell);
    virtual ~Cell();
private:
    Q_DISABLE_COPY(Cell)
    SudokuSolver::Core::Cell* _cell;
    bool _cleanupCell;
};

}}

#endif

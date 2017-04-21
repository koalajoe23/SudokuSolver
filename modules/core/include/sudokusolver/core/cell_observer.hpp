#ifndef SUDOKUSOLVER_CORE_CELL_OBSERVER_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_CELL_OBSERVER_HPP_INCLUDED

#include<vector>
#include<algorithm>

#include <sudokusolver/core/cell.hpp>

namespace SudokuSolver { namespace Core {

class Cell;
class CellObserver {

public:
    virtual ~CellObserver() {}
    virtual void cellValueChanged(const Cell& cell, Cell::ValueType value) = 0;
    virtual void cellStateChanged(const Cell& cell, Cell::StateType value) = 0;
};

}}

#endif //SUDOKUSOLVER_CORE_CELL_OBSERVER_HPP_INCLUDED

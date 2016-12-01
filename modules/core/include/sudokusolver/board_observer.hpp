#ifndef SUDOKUSOLVER_CORE_BOARD_OBSERVER_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_BOARD_OBSERVER_HPP_INCLUDED

#include<vector>
#include<algorithm>

#include <sudokusolver/cell_observer.hpp>

namespace SudokuSolver { namespace Core {

class Board;
class BoardObserver {

public:


    virtual ~BoardObserver() {}

    // BoardObserver interface
public:
    virtual void boardCellValueChanged(const Board& board, const Cell& cell, Cell::ValueType value) = 0;
    virtual void boardCellStateChanged(const Board& board, const Cell& cell, Cell::StateType value) = 0;
};

}}

#endif //SUDOKUSOLVER_CORE_BOARD_OBSERVER_HPP_INCLUDED

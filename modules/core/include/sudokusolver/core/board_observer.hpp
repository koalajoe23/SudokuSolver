#ifndef SUDOKUSOLVER_CORE_BOARD_OBSERVER_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_BOARD_OBSERVER_HPP_INCLUDED

#include<vector>
#include<algorithm>

#include <sudokusolver/core/board.hpp>

namespace SudokuSolver { namespace Core {

class BoardObserver {

public:


    virtual ~BoardObserver() {}

    // BoardObserver interface
public:
    virtual void boardCellValueChanged(const Board::iterator& board, Cell::ValueType value) = 0;
    virtual void boardCellStateChanged(const Board::iterator& board, Cell::StateType value) = 0;
};

}}

#endif //SUDOKUSOLVER_CORE_BOARD_OBSERVER_HPP_INCLUDED

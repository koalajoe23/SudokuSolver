#ifndef SUDOKUSOLVER_CORE_SOLVER_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_SOLVER_HPP_INCLUDED

#include <sudokusolver/core/board.hpp>

namespace SudokuSolver { namespace Core {

class Solver {
public:

    enum AnalyzationResultType {
        //the order of the following is important! uncertain -> certain
          RESULT_VALID = 0
        , RESULT_INDETERMINATE
        , RESULT_INVALID

        , RESULT_COUNT
    };

    class Analyzer {
    public:
        static Solver::AnalyzationResultType analyze(const Board& board);
    private:
        //FIXME: First parameter is called by reference, need to implement const_iterator to make both const&
        static Solver::AnalyzationResultType analyzeIterator(Board::iterator& startIterator, Board::iterator& endIterator);

        static Solver::AnalyzationResultType analyzeRow(const Board& board, unsigned int row);
        static Solver::AnalyzationResultType analyzeColumn(const Board& board, unsigned int column);
        static Solver::AnalyzationResultType analyzeBoxes(const Board& board);

        static Solver::AnalyzationResultType mergeResults(Solver::AnalyzationResultType lhs, Solver::AnalyzationResultType rhs);
    };

    static AnalyzationResultType solve(Board& board);

};

}}

#endif //SUDOKUSOLVER_CORE_SOLVER_HPP_INCLUDED

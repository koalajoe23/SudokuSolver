#include <sudokusolver/core/solver.hpp>

#include <set>
#include <assert.h>

using namespace SudokuSolver::Core;

Solver::AnalyzationResultType Solver::Analyzer::analyze(const Board& constBoard)
{
    //TODO: const_iterator implementieren
    Board& board = *const_cast<Board*>(&constBoard);

    Solver::AnalyzationResultType result = Solver::RESULT_VALID;

    //traverse diagonally
    for(Board::diagonal_iterator diagonalBoardIterator = board.begin(); diagonalBoardIterator != board.end(); ++diagonalBoardIterator)
    {
        //ROW

        //the stronger result prevails VALID -> INDETERMINATE -> INVALID
        result = mergeResults(result, analyzeRow(board, diagonalBoardIterator.yPosition()));
        assert(result >= 0 && result < Solver::RESULT_COUNT && "enum result out of bounds!");

        //If we found 1 invalid row/column/square the whole board is invalid, no use for further searching
        if(result == Solver::RESULT_INVALID)
        {
            break;
        }

        //COLUMN

        //the stronger result prevails VALID -> INDETERMINATE -> INVALID
        result = mergeResults(result, analyzeColumn(board, diagonalBoardIterator.xPosition()));
        assert(result >= 0 && result < Solver::RESULT_COUNT && "enum result out of bounds!");

        //If we found 1 invalid row/column/square the whole board is invalid, no use for further searching
        if(result == Solver::RESULT_INVALID)
        {
            break;
        }
    }

    //the stronger result prevails VALID -> INDETERMINATE -> INVALID
    result = mergeResults(result, analyzeBoxes(board));
    assert(result >= 0 && result < Solver::RESULT_COUNT && "enum result out of bounds!");

    return result;
}

Solver::AnalyzationResultType Solver::Analyzer::analyzeIterator(Board::iterator& startIterator, Board::iterator& endIterator)
{
    Solver::AnalyzationResultType result = Solver::RESULT_VALID;

    std::set<Cell::ValueType> values = {
          Cell::VALUE_ONE
        , Cell::VALUE_TWO
        , Cell::VALUE_THREE
        , Cell::VALUE_FOUR
        , Cell::VALUE_FIVE
        , Cell::VALUE_SIX
        , Cell::VALUE_SEVEN
        , Cell::VALUE_EIGHT
        , Cell::VALUE_NINE
    };

    for(; startIterator != endIterator; ++startIterator)
    {
        Cell& cell = *startIterator;

        if(cell.value() == Cell::VALUE_UNSET)
        {
            result = Solver::RESULT_INDETERMINATE;

            //No need to further process
            continue;
        }

        //look for value in values-set. If not found: duplicate value, row is invalid, else erase and carry on
        std::set<Cell::ValueType>::iterator value = values.find(cell.value());
        if(value == values.end())
        {
            result = Solver::RESULT_INVALID;
            break;
        }
        else
        {
            values.erase(value);
        }
    }

    return result;
}

Solver::AnalyzationResultType Solver::Analyzer::analyzeRow(const Board& constBoard, unsigned int row)
{
    //TODO: const_iterator implementieren
    Board& board = *const_cast<Board*>(&constBoard);

    Board::iterator startIterator = board.begin_row(row);
    Board::iterator endIterator = board.end_row(row);

    return Solver::Analyzer::analyzeIterator(startIterator, endIterator);
}

Solver::AnalyzationResultType Solver::Analyzer::analyzeColumn(const Board& constBoard, unsigned int column)
{
    //TODO: const_iterator implementieren
    Board& board = *const_cast<Board*>(&constBoard);

    Board::vertical_iterator startIterator = board.begin_column(column);
    Board::vertical_iterator endIterator = board.end_column(column);

    //We need the cast to vertical_iterator so we don't traverse rows
    return Solver::Analyzer::analyzeIterator(startIterator, endIterator);
}

Solver::AnalyzationResultType Solver::Analyzer::analyzeBoxes(const Board& constBoard)
{
    //TODO: const_iterator implementieren
    Board& board = *const_cast<Board*>(&constBoard);

    Solver::AnalyzationResultType result = Solver::RESULT_VALID;

    for(int box=0; box < Board::SIZE; ++box)
    {
        Board::box_iterator boxStartIterator(board, box);

        //Start of lower box is end of current Box
        //Can be out of bounds, so no range checks please
        Board::box_iterator boxEndIterator(board, box + 3);

        result = mergeResults(result, Solver::Analyzer::analyzeIterator(boxStartIterator, boxEndIterator));
    }

    return result;
}

Solver::AnalyzationResultType Solver::Analyzer::mergeResults(Solver::AnalyzationResultType lhs, Solver::AnalyzationResultType rhs)
{
    //the stronger result prevails VALID -> INDETERMINATE -> INVALID
    return static_cast<Solver::AnalyzationResultType>(
                 std::max(
                       static_cast<int>(lhs)
                     , static_cast<int>(rhs)
                     )
                 );
}

Solver::AnalyzationResultType Solver::solve(Board& board)
{
    AnalyzationResultType result = RESULT_VALID;
    board.reset();
    Board::editable_iterator boardIterator(board.begin());

    while(boardIterator != board.end())
    {
        if(boardIterator->value() == Cell::VALUE_UNSET)
        {
            boardIterator->setNextValue();
        }

        result = Analyzer::analyze(board);

        if(Solver::RESULT_VALID == result)
        {
            //Solved!
            return result;
        }
        else if(Solver::RESULT_INDETERMINATE == result)
        {
            ++boardIterator;
        }
        else if(Solver::RESULT_INVALID == result)
        {
            while(boardIterator->hasNextValue() == false)
            {
                boardIterator->resetValue();
                --boardIterator;

                if(boardIterator == board.rend())
                {
                    //Unsolvable
                    return result;
                }
            }

            boardIterator->setNextValue();
        }
    }

    return result;

}

#include <cstdlib>
#include <iostream>
#include <cassert>

#include <sudokusolver/solver.hpp>

int main(int argc, char* argv[])
{
    using namespace SudokuSolver;

    std::string str;

    if(argc > 1)
    {
        str = std::string(argv[1]);
    }
    else
    {
        std::cout << "Please pass Sudoku string as command line argument. Aborting!" << std::endl;
        //str = "001230000004000000003000451000302006500040002100507000869000700000000800000095100";
        return EXIT_FAILURE;
    }

    try
    {
        Core::Board board = Core::Board::Parser::fromStdString(str);

        std::cout << "Solving Sudoku..." << std::endl;
        std::cout << "INPUT:  " << Core::Board::Parser::toStdString(board) << std::endl;
        Core::Solver::AnalyzationResultType result = Core::Solver::solve(board);

        if(Core::Solver::RESULT_VALID == result)
        {
            std::cout << "OUTPUT: " <<Core::Board::Parser::toStdString(board) << std::endl;
        }
        else if(Core::Solver::RESULT_INVALID == result)
        {
            std::cout << "Sudoku is not solvable." << std::endl;
        }
        assert(Core::Solver::RESULT_INDETERMINATE != result);

        return EXIT_SUCCESS;
    }
    catch(std::exception ex)
    {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }
}

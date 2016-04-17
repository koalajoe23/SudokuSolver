#include <cstdlib>
#include <iostream>

#include <sudokusolver/solver.hpp>

int main(int argc, char* argv[])
{
    using namespace SudokuSolver;

    /*SudokuSolver::Core::Cell cell;

    std::cout << "Cell state: " << cell.state() << ", value: " << cell.value() << std::endl;

    try
    {
        while(cell.hasNextValue())
        {
            cell.setNextValue();
            std::cout << "Cell state: " << cell.state() << ", value: " << cell.value() << std::endl;
        }
    }
    catch(std::exception& ex)
    {
        const char* msg = ex.what();
        std::cerr << "[FATAL ERROR] " << msg << std::endl;
        return EXIT_FAILURE;
    }*/

    std::string str = "X9X" "XXX" "24X"
                      "5X6" "XXX" "9XX"
                      "X37" "6X9" "85X"

                      "XX2" "X6X" "X7X"
                      "968" "7X4" "XXX"
                      "4X3" "1XX" "XXX"

                      "XXX" "48X" "XX3"
                      "XXX" "2X7" "XX5"
                      "XXX" "XX1" "XXX";

    /*std::string str = "891" "375" "246"
                      "546" "812" "937"
                      "237" "649" "851"

                      "152" "963" "478"
                      "968" "754" "312"
                      "473" "128" "569"

                      "725" "486" "193"
                      "314" "297" "685"
                      "689" "531" "724";*/

    Core::Board board = Core::Board::Parser::fromStdString(str);

    std::cout << Core::Board::Parser::toStdString(board) << std::endl;
    Core::Solver::solve(board);
    std::cout << Core::Board::Parser::toStdString(board) << std::endl;

    return EXIT_SUCCESS;
}

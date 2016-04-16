#include <cstdlib>
#include <iostream>

#include <sudokusolver/board.hpp>

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

    Core::Board board;

    board.cell(4,7).setState(Core::Cell::STATE_FIXED);

    for(Core::Board::editable_iterator cellIterator = board.begin(); cellIterator != board.end(); ++cellIterator)
    {
        std::cout << "Cell(" << cellIterator.xPosition() << "," << cellIterator.yPosition() << ")" << std::endl;
    }

    return EXIT_SUCCESS;
}

#include <sudokusolver/board.hpp>

#include <assert.h>

using namespace SudokuSolver::Core;


Board::iterator::iterator(Board& board, int xPosition, int yPosition)
    : m_board(board)
    , m_xPosition(xPosition)
    , m_yPosition(yPosition)
{

}

Board::iterator::iterator(const Board::iterator& rhs)
    : m_board(rhs.m_board)
{
    *this = rhs;
}

Board::iterator::~iterator()
{

}

Board::iterator& Board::iterator::operator=(const Board::iterator& rhs)
{
    m_board = rhs.m_board;
    m_xPosition = rhs.m_xPosition;
    m_yPosition = rhs.m_yPosition;

    return *this;
}

Board::iterator& Board::iterator::operator++()
{
    //if y is already maxed, put it back to zero and increment x instead
    if(Board::SIZE - 1 == m_yPosition)
    {
        ++m_xPosition;
        m_yPosition = 0;
    }
    //common case: just increment y
    else
    {
        ++m_yPosition;
    }
}

Board::iterator&Board::iterator::operator--()
{
    //if y is already null, put it back to maximum value and decrement x instead
    if(0 == m_yPosition)
    {
        --m_xPosition;
        m_yPosition = Board::SIZE - 1;
    }
    //common case: just decrement y
    else
    {
        --m_yPosition;
    }
}

Board::iterator Board::iterator::operator++(int)
{
    iterator returnValue(*this);
    ++(*this);

    return returnValue;
}

Board::iterator Board::iterator::operator--(int)
{
    iterator returnValue(*this);
    --(*this);

    return returnValue;
}

bool Board::iterator::operator==(const Board::iterator& rhs) const
{
    return (   &m_board == &rhs.m_board
            && m_xPosition == rhs.m_xPosition
            && m_yPosition == rhs.m_yPosition);
}

bool Board::iterator::operator!=(const Board::iterator& rhs) const
{
    return !(*this == rhs);
}

Cell& Board::iterator::operator->() const
{
    //FIXME: Can I just call operator*()?
    return m_board.cell(m_xPosition, m_yPosition);
}

Cell& Board::iterator::operator*() const
{
    return m_board.cell(m_xPosition, m_yPosition);
}

int Board::iterator::yPosition() const
{
    return m_yPosition;
}

int Board::iterator::xPosition() const
{
    return m_xPosition;
}

Board::Board()
    : m_cells()
{

}

Board::Board(const Board& rhs)
{
    *this = rhs;
}

Board::~Board()
{

}

Board& Board::operator=(const Board& rhs)
{
    m_cells = rhs.m_cells;

    return *this;
}

Board::iterator Board::begin()
{
    return Board::iterator(*this);
}

Board::iterator Board::end()
{
    return Board::iterator(*this, Board::SIZE, 0); //1 field out of bounds
}

Board::iterator Board::rbegin()
{
    return Board::iterator(*this, Board::SIZE - 1, Board::SIZE - 1); //1 field out of bounds
}

Board::iterator Board::rend()
{
    return Board::iterator(*this, -1, Board::SIZE - 1);
}

Cell& Board::cell(unsigned int xPosition, unsigned int yPosition)
{
    if(xPosition < Board::SIZE && yPosition < Board::SIZE)
    {
        return m_cells[xPosition][yPosition];
    }
    else
    {
        std::string operation = std::string("cell(") + std::to_string(xPosition)+ std::string(",") + std::to_string(yPosition) + std::string(")");
        throw Board::IllegalOperationException(*this, operation);
    }
}

const char* Board::Exception::what() const throw ()
{
    return m_message.c_str();
}

const Board& Board::Exception::board() const
{
    return *m_board;
}

Board::Exception::Exception(const Board& board)
    : m_board(&board)
    , m_message("Board Exception: ")
{

}

Board::Exception::Exception(const Board::Exception& rhs)
{
    *this = rhs;
}

Board::Exception::~Exception()
{

}

Board::Exception&Board::Exception::operator=(const Board::Exception& rhs)
{
    m_board = rhs.m_board;
    m_message = rhs.m_message;
}

Board::IllegalOperationException::IllegalOperationException(const Board& board, const std::string& operation)
    : Board::Exception(board)
    , m_operation(operation)
{
    m_message = m_message + std::string("Illegal operation ") + m_operation;
}

Board::IllegalOperationException::~IllegalOperationException()
{

}

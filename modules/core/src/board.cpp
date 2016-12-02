#include <sudokusolver/board.hpp>
#include <sudokusolver/board_observer.hpp>
#include <assert.h>

using namespace SudokuSolver::Core;


Board::iterator::iterator(Board& board, int xPosition, int yPosition)
    : m_board(board)
    , m_xPosition(xPosition)
    , m_yPosition(yPosition)
{

}

Board::iterator::iterator(Board& board, const Cell& cell)
    : m_board(board)
{
    //XXX: I am not smart enough right now to use std::find :/

    //XXX: const_cast wouldn't be needed if Board::const_iterator would be implemented...
    //Cell* unconstCell = const_cast<Cell*>(&cell);
    //Board::iterator iter = std::find(begin(), end(), *cell);
    //Board::iterator iter = begin();

    Board::iterator found = m_board.end();
    for(Board::iterator iter = m_board.begin(); iter != m_board.end(); ++iter)
    {
        Cell* current = &(*iter);
        if(current == &cell)
        {
            found = iter;
            break;
        }
    }

    m_xPosition = found.xPosition();
    m_yPosition = found.yPosition();
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
    //if x is already maxed, put it back to zero and increment y instead
    if(Board::SIZE - 1 == m_xPosition)
    {
        ++m_yPosition;
        m_xPosition = 0;
    }
    //common case: just increment x
    else
    {
        ++m_xPosition;
    }

    return *this;
}

Board::iterator& Board::iterator::operator--()
{
    //if x is already null, put it back to maximum value and decrement y instead
    if(0 == m_xPosition)
    {
        --m_yPosition;
        m_xPosition = Board::SIZE - 1;
    }
    //common case: just decrement y
    else
    {
        --m_xPosition;
    }

    return *this;
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

Cell* Board::iterator::operator->() const
{
    return &this->operator *();
}

Cell& Board::iterator::operator*() const
{
    return m_board.cell(m_xPosition, m_yPosition);
}

int Board::iterator::yPosition() const
{
    return m_yPosition;
}

Board&Board::iterator::board() const
{
    return m_board;
}

int Board::iterator::xPosition() const
{
    return m_xPosition;
}

Board::Board()
    : Observable<BoardObserver>()
    , m_cells()
{
    //Register board as cell listener for all cells
    for(iterator iter = begin(); iter != end(); ++iter)
    {
        iter->addObserver(*this);
    }
}

Board::Board(const Board& rhs)
    : Observable<BoardObserver>()
    , m_cells()
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
    return begin_row(0);
}

Board::iterator Board::end()
{
    return end_row(Board::SIZE - 1);
}

Board::iterator Board::rbegin()
{
    return Board::iterator(*this, Board::SIZE - 1, Board::SIZE - 1); //1 field out of bounds
}

Board::iterator Board::rend()
{
    return Board::iterator(*this, Board::SIZE - 1, -1);
}

Board::iterator Board::begin_row(unsigned int row)
{
    if(row >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("begin_row(" + std::to_string(row) + std::string(")")));
    }
    return Board::iterator(*this, 0, row);
}

Board::iterator Board::end_row(unsigned int row)
{
    if(row >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("end_row(" + std::to_string(row) + std::string(")")));
    }
    return Board::iterator(*this, 0, row + 1);
}

Board::iterator Board::rbegin_row(unsigned int row)
{
    if(row >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("rbegin_row(" + std::to_string(row) + std::string(")")));
    }
    return Board::iterator(*this, Board::SIZE - 1, row);
}

Board::iterator Board::rend_row(unsigned int row)
{
    if(row >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("rend_row(" + std::to_string(row) + std::string(")")));
    }
    return Board::iterator(*this, Board::SIZE - 1, row - 1);
}

Board::vertical_iterator Board::begin_column(unsigned int column)
{
    if(column >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("begin_column(" + std::to_string(column) + std::string(")")));
    }
    return Board::vertical_iterator(*this, column, 0);
}

Board::vertical_iterator Board::end_column(unsigned int column)
{
    if(column >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("end_column(" + std::to_string(column) + std::string(")")));
    }
    return Board::vertical_iterator(*this, column + 1, 0);
}

Board::vertical_iterator Board::rbegin_column(unsigned int column)
{
    if(column >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("rbegin_column(" + std::to_string(column) + std::string(")")));
    }
    return Board::vertical_iterator(*this, column, Board::SIZE - 1);
}

Board::vertical_iterator Board::rend_column(unsigned int column)
{
    if(column >= Board::SIZE)
    {
        throw Board::IllegalOperationException(*this, std::string("rend_column(" + std::to_string(column) + std::string(")")));
    }
    return Board::vertical_iterator(*this, column - 1, Board::SIZE - 1);
}
#include <iostream>
void Board::cellValueChanged(const Cell& cell, Cell::ValueType value)
{
    Board::iterator found(*this, cell);
    assert(found != end());

    std::function<void(BoardObserver&, const Board::iterator&, Cell::ValueType)> valueChangedFunc = std::mem_fn(&BoardObserver::boardCellValueChanged);
    std::function<void(BoardObserver&)> parameterizedValueChangedFunc = std::bind(valueChangedFunc, std::placeholders::_1, found, value);
    notifyObservers(parameterizedValueChangedFunc);
}

void Board::cellStateChanged(const Cell& cell, Cell::StateType state)
{
    Board::iterator found(*this, cell);
    assert(found != end());

    std::function<void(BoardObserver&, const Board::iterator&, Cell::StateType)> stateChangedFunc = std::mem_fn(&BoardObserver::boardCellStateChanged);
    std::function<void(BoardObserver&)> parameterizedStateChangedFunc = std::bind(stateChangedFunc, std::placeholders::_1, found, state);
    notifyObservers(parameterizedStateChangedFunc);
}

Cell& Board::cell(unsigned int xPosition, unsigned int yPosition)
{
    if(    xPosition < Board::SIZE
        && yPosition < Board::SIZE
        && xPosition >= 0
        && yPosition >= 0)
    {
        return m_cells[yPosition][xPosition];
    }
    else
    {
        std::string operation = std::string("cell(") + std::to_string(xPosition)+ std::string(",") + std::to_string(yPosition) + std::string(")");
        throw Board::IllegalOperationException(*this, operation);
    }
}

void Board::reset()
{
    for(Board::editable_iterator editableIterator(begin()); editableIterator != end(); ++editableIterator)
    {
        editableIterator->resetValue();
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

Board::editable_iterator::editable_iterator(Board& board, int xPosition, int yPosition)
    : Board::iterator(board, xPosition, yPosition)
{
    if(m_board.cell(m_xPosition, m_yPosition).state() != Cell::STATE_EDITABLE)
    {
        //This forwards to the next editable cell
        operator++();
    }
}

Board::editable_iterator::editable_iterator(const Board::iterator& iterator)
    : Board::iterator(iterator)
{
    //FIXME: Redundancy to other ctor
    if(m_board.cell(m_xPosition, m_yPosition).state() != Cell::STATE_EDITABLE)
    {
        //This forwards to the next editable cell
        operator++();
    }
}

Board::editable_iterator::~editable_iterator()
{

}

Board::editable_iterator& Board::editable_iterator::operator++()
{
    iterator end = m_board.end();
    if (m_board.end() == *this)
    {
        return *this;
    }

    do
    {
        Board::iterator::operator ++();
    }
    while(   m_board.end() != *this
          && m_board.cell(m_xPosition, m_yPosition).state() == Cell::STATE_FIXED);

    return *this;
}

Board::editable_iterator& Board::editable_iterator::operator--()
{
    if(m_board.rend() == *this)
    {
        return *this;
    }

    do
    {
        Board::iterator::operator --();
    }
    while(   m_board.rend() != *this
          && m_board.cell(m_xPosition, m_yPosition).state() == Cell::STATE_FIXED);

    return *this;
}

Board Board::Parser::fromStdString(const std::string& boardStr)
{
    //throw if string is too short or long for board
    if(boardStr.length() != Board::SIZE * Board::SIZE)
    {
        //TODO: exception
        throw 0;
    }

    Board board;

    iterator boardIterator = board.begin();

    for(std::string::const_iterator characterIter = boardStr.cbegin(); characterIter != boardStr.cend(); ++characterIter)
    {
        const char character = *characterIter;

        Cell& cell = *boardIterator;
        std::string charStr(1, character);
        cell = Cell::Parser::fromStdString(charStr);

        //a cell should be either editable or having value
        assert(   (boardIterator->state() == Cell::STATE_EDITABLE)
               != (boardIterator->value() != Cell::VALUE_UNSET)
              );

        //go to next field on board
        ++boardIterator;
    }

    return board;
}

std::string Board::Parser::toStdString(const Board& constBoard)
{
    std::string returnValue;
    returnValue.reserve(Board::SIZE * Board::SIZE);

    //FIXME: const_iterator would be nicer
    Board& board = *const_cast<Board*>(&constBoard);
    for(Board::iterator boardIterator = board.begin(); boardIterator != board.end(); ++boardIterator)
    {
        returnValue += Cell::Parser::toStdString(*boardIterator);
    }

    return returnValue;
}

Board::vertical_iterator::vertical_iterator(Board& board, int xPosition, int yPosition)
    : Board::iterator(board, xPosition, yPosition)
{

}

Board::vertical_iterator::vertical_iterator(const Board::iterator& iterator)
     : Board::iterator(iterator)
{

}

Board::vertical_iterator::~vertical_iterator()
{

}

Board::vertical_iterator& Board::vertical_iterator::operator++()
{
    //NOTE: this is the exact same function as iterator::operator++ only with xPosition and yPosition swapped
    //FIXME: Refactor into shared function

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

    return *this;
}

Board::vertical_iterator& Board::vertical_iterator::operator--()
{
    //if y is already null, put it back to maximum value and decrement x instead
    if(0 == m_yPosition)
    {
        --m_xPosition;
        m_yPosition = Board::SIZE - 1;
    }
    //common case: just decrement x
    else
    {
        --m_yPosition;
    }

    return *this;
}

Board::diagonal_iterator::diagonal_iterator(Board& board, int xPosition, int yPosition)
    : Board::iterator(board, xPosition, yPosition)
{

}

Board::diagonal_iterator::diagonal_iterator(const Board::iterator& iterator)
    : Board::iterator(iterator)
{

}

Board::diagonal_iterator::~diagonal_iterator()
{

}

Board::diagonal_iterator&Board::diagonal_iterator::operator++()
{
    ++m_xPosition;
    ++m_yPosition;

    //if we go 1 beyond the last cell we are at (Board::SIZE,Board::SIZE), but the default (horizontal) end iterator is (0, Board::SIZE)
    //let's correct that
    if(m_xPosition == Board::SIZE || m_yPosition == Board::SIZE)
    {
        m_xPosition = 0;
        m_yPosition = Board::SIZE;
    }

    return *this;
}

Board::diagonal_iterator&Board::diagonal_iterator::operator--()
{
    --m_xPosition;
    --m_yPosition;

    //if we go 1 beyond the last cell we are at (Board::SIZE,Board::SIZE), but the default (horizontal) end iterator is (0, Board::SIZE)
    //let's correct that
    if(m_xPosition == -1 || m_yPosition == -1)
    {
        m_xPosition = Board::SIZE - 1;
        m_yPosition = -1;
    }

    return *this;
}

Board::box_iterator::box_iterator(Board& board, unsigned int box)
    : Board::iterator(board, 0, 0) //< x & y position will be changed in function body
    , m_box(box)
{
    //Get first cell of box (upper left)
    m_xPosition = (m_box * Board::BOX_SIZE) % Board::SIZE;
    m_yPosition = std::floor(m_box * Board::BOX_SIZE / Board::SIZE) * Board::BOX_SIZE;
}

Board::box_iterator::box_iterator(const Board::iterator& iterator)
    : Board::iterator(iterator)
{

}

Board::box_iterator::~box_iterator()
{

}

Board::box_iterator& Board::box_iterator::operator++()
{
    m_xPosition++;

    if(m_xPosition == ((m_box * Board::BOX_SIZE) % Board::SIZE) + 3)
    {
        m_xPosition = ((m_box * Board::BOX_SIZE) % Board::SIZE);
        ++m_yPosition;
    }
}

Board::box_iterator& Board::box_iterator::operator--()
{
    //FIXME implement backwards box iteration. It is not needed right now

    throw("Not Implemented!");
}

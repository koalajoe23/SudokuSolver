#include <sudokusolver/cell.hpp>

using namespace SudokuSolver::Core;

Cell::Cell(Cell::StateType state /*= Cell::STATE_EDITABLE*/, Cell::ValueType value /*= Cell::VALUE_UNSET*/)
{
    //a fixed cell can not be unset
    if(Cell::STATE_FIXED == state && Cell::VALUE_UNSET == value)
    {
        throw Cell::IllegalStateException(*this);
    }
}

Cell::Cell(const Cell& rhs)
{
    *this = rhs;
}

Cell::~Cell()
{

}

Cell&Cell::operator=(const Cell& rhs)
{
    m_state = rhs.m_state;
    m_value = rhs.m_value;
}

Cell::ValueType Cell::value() const
{
    return m_value;
}

Cell::StateType Cell::state() const
{
    return m_state;
}

bool Cell::hasNextValue() const
{
    return Cell::STATE_EDITABLE == m_state && Cell::VALUE_NINE != m_value;
}

void Cell::setNextValue()
{
    if(hasNextValue())
    {
        m_value = static_cast<Cell::ValueType>(static_cast<int>(m_value) + 1);
    }
    else
    {
        throw Cell::IllegalOperationException(*this, __FUNCTION__);
    }
}

void Cell::resetValue()
{
    if(Cell::STATE_EDITABLE == m_state)
    {
        m_value = Cell::VALUE_UNSET;
    }
    else
    {
        throw Cell::IllegalOperationException(*this, __FUNCTION__);
    }
}

void Cell::setState(Cell::StateType state)
{
    m_state = state;
}

Cell::IllegalStateException::IllegalStateException(const Cell& cell)
    : Cell::Exception(cell)
{
    m_message += "Illegal cell state";
}

Cell::IllegalStateException::~IllegalStateException()
{

}

Cell::Exception::Exception(const Cell& cell)
    : m_cell(&cell)
    , m_message("Cell(state => " + std::to_string(m_cell->state()) + ", value => " + std::to_string(m_cell->value()) + "): ")
{

}

Cell::Exception::Exception(const Cell::Exception& rhs)
    : m_cell(rhs.m_cell)
{
    *this = rhs;
}

Cell::Exception::~Exception()
{

}

Cell::Exception& Cell::Exception::operator=(const Cell::Exception& rhs)
{
     this->m_cell = rhs.m_cell;
     m_message = rhs.m_message;

     return *this;
}

const char* Cell::Exception::what() const throw ()
{
    return m_message.c_str();
}

const Cell& Cell::Exception::cell() const
{
    return *m_cell;
}

Cell::IllegalOperationException::IllegalOperationException(const Cell& cell, const std::string& operation)
    : Cell::Exception(cell)
    , m_operation(operation)
{
    m_message += std::string("Illegal cell operation ") + std::string(m_operation);
}

Cell::IllegalOperationException::~IllegalOperationException()
{

}

#include <sudokusolver/cell.hpp>

#include <assert.h>

using namespace SudokuSolver::Core;

Cell::Cell(Cell::StateType state /*= Cell::STATE_EDITABLE*/, Cell::ValueType value /*= Cell::VALUE_UNSET*/)
    : m_state(state)
    , m_value(value)
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

Cell& Cell::operator=(const Cell& rhs)
{
    m_state = rhs.m_state;
    m_value = rhs.m_value;

    return *this;
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

void Cell::setValue(Cell::ValueType value)
{
    m_value = value;
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

Cell Cell::Parser::fromStdString(const std::string& cellStr)
{
    //FIXME: Ugly code

    if (cellStr.length() != 1)
    {
        //TODO: Exception illegal input length (should be 1 character)
        throw 0;
    }

    if ("X" == cellStr)
    {
        return Cell(STATE_EDITABLE, VALUE_UNSET);
    }

    if ("1" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_ONE);
    }

    if ("2" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_TWO);
    }

    if ("3" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_THREE);
    }

    if ("4" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_FOUR);
    }

    if ("5" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_FIVE);
    }

    if ("6" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_SIX);
    }

    if ("7" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_SEVEN);
    }

    if ("8" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_EIGHT);
    }

    if ("9" == cellStr)
    {
        return Cell(STATE_FIXED, VALUE_NINE);
    }

    //found nothing... that means we have an illegal char
    //TODO: Exception illegal input string
    throw 0;

    return Cell();
}

std::string Cell::Parser::toStdString(const Cell& cell)
{
    //FIXME: Ugly code

    if(cell.state() == STATE_EDITABLE)
    {
        return "X";
    }

    //VALUE_UNSET cannot occur when state != STATE_EDITABLE
    //see ctor
    assert(cell.value() != VALUE_UNSET);

    switch(cell.value())
    {
        case VALUE_ONE: return std::string("1");
        case VALUE_TWO: return std::string("2");
        case VALUE_THREE: return std::string("3");
        case VALUE_FOUR: return std::string("4");
        case VALUE_FIVE: return std::string("5");
        case VALUE_SIX: return std::string("6");
        case VALUE_SEVEN: return std::string("7");
        case VALUE_EIGHT: return std::string("8");
        case VALUE_NINE: return std::string("9");
        default: assert(false && "Illegal cell value. How did this happen?");
    }
}

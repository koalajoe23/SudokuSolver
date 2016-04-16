#ifndef SUDOKUSOLVER_CORE_CELL_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_CELL_HPP_INCLUDED

#include <exception>
#include <string>


namespace SudokuSolver { namespace Core {

    class Cell
    {
    public:
        enum ValueType {
              VALUE_UNSET = 0
            , VALUE_ONE = 1
            , VALUE_TWO = 2
            , VALUE_THREE = 3
            , VALUE_FOUR = 4
            , VALUE_FIVE = 5
            , VALUE_SIX = 6
            , VALUE_SEVEN = 7
            , VALUE_EIGHT = 8
            , VALUE_NINE = 9

            , VALUE_COUNT //<< Determine Value Count
        };

        enum StateType {
              STATE_EDITABLE = 0
            , STATE_FIXED

            , STATE_COUNT //<Determine State count
        };
    public:
        class Exception : public std::exception
        {
            // exception interface
        public:
            virtual const char* what() const throw ();
            const Cell& cell() const;

        protected:
            Exception(const Cell& cell);
            Exception(const Exception& rhs);
            virtual ~Exception();
            Exception& operator=(const Exception& rhs);
        protected:
            const Cell* m_cell;
            std::string m_message;
        };
        class IllegalStateException : public Exception
        {
        public:
            explicit IllegalStateException(const Cell& cell);
            virtual ~IllegalStateException();
        };
        class IllegalOperationException : public Exception
        {
        public:
            explicit IllegalOperationException(const Cell& cell, const std::string& operation);
            virtual ~IllegalOperationException();

        private:
            std::string m_operation;
        };

        class Parser {
        public:
            static Cell fromStdString(const std::string& cellStr);
            static std::string toStdString(const Cell& cell);
        };

        Cell(StateType state = STATE_EDITABLE, ValueType value = VALUE_UNSET);
        Cell(const Cell& rhs);
        virtual ~Cell();
        Cell& operator=(const Cell& rhs);
        ValueType value() const;
        StateType state() const;
        bool hasNextValue() const;
        void setNextValue();
        void resetValue();
        void setState(StateType state);
        void setValue(ValueType value);

    private:
        ValueType m_value;
        StateType m_state;
    };
}}

#endif // SUDOKUSOLVER_CORE_CELL_HPP_INCLUDED

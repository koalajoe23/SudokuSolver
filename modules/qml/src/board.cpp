#include <sudokusolver/qml/board.hpp>
#include <QDebug>

using namespace SudokuSolver;

Qml::Board::Board()
    : QAbstractItemModel(nullptr)
    , _board(new Core::Board())
    , _cleanupBoard(true)
    , _cells(Core::Board::SIZE, QVector<Cell*>(Core::Board::SIZE))
{
    initCells();
}

Qml::Board::Board(QObject* parent)
    : QAbstractItemModel(parent)
    , _board(new Core::Board())
    , _cleanupBoard(true)
    , _cells(Core::Board::SIZE, QVector<Cell*>(Core::Board::SIZE))
{
    initCells();
}

Qml::Board::Board(Core::Board& board)
    : QAbstractItemModel(nullptr)
    , _board(&board)
    , _cleanupBoard(false)
    , _cells(Core::Board::SIZE, QVector<Cell*>(Core::Board::SIZE))
{
    initCells();
}

Qml::Board::~Board()
{
    for(QVector< QVector<Cell*> >::iterator xIterator = _cells.begin(); xIterator != _cells.end(); ++xIterator)
    {
        unsigned int yPos = 0;
        for(QVector<Cell*>::iterator cellIterator = xIterator->begin(); cellIterator != xIterator->end(); ++cellIterator)
        {
            Cell* cell = *cellIterator;
            xIterator->replace(yPos, nullptr);
            delete cell;
            ++yPos;
        }
    }

    if(_cleanupBoard && _board != nullptr)
    {
        delete(_board);
    }
    _board = nullptr;
}

QModelIndex Qml::Board::index(int row, int column, const QModelIndex& parent) const
{
    return createIndex(row, column, nullptr);
}

QModelIndex Qml::Board::parent(const QModelIndex& child) const
{
    return QModelIndex();
}

int Qml::Board::rowCount(const QModelIndex& parent) const
{
    return (int)Core::Board::SIZE;
}

int Qml::Board::columnCount(const QModelIndex& parent) const
{
    return (int)Core::Board::SIZE;
}

QVariant Qml::Board::data(const QModelIndex& index, int role) const
{
    //TODO implement Cell return
    return QVariant("UNIMPLEMENTED");
}

quint32 Qml::Board::size() const
{
    return (int)Core::Board::SIZE;
}

void Qml::Board::initCells()
{
    for(Core::Board::iterator cellIterator = _board->begin(); cellIterator != _board->end(); ++cellIterator)
    {
        //Created cells have to be deallocated in destructor
        _cells[cellIterator.xPosition()][cellIterator.yPosition()] = new Cell(*cellIterator);
    }
    return;
}

QHash<int, QByteArray> SudokuSolver::Qml::Board::roleNames() const
{
    QHash<int, QByteArray> roleNames = QAbstractItemModel::roleNames();
    roleNames.insert(CELL_ROLE, "cell");
    return roleNames;
}

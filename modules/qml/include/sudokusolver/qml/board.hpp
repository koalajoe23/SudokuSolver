#ifndef SUDOKUSOLVER_QML_BOARD_HPP_INCLUDED
#define SUDOKUSOLVER_QML_BOARD_HPP_INCLUDED

#include <QAbstractItemModel>

#include <sudokusolver/core/board.hpp>
#include <sudokusolver/qml/cell.hpp>

namespace SudokuSolver { namespace Qml {

class Board : public QAbstractItemModel {
    Q_OBJECT
    Q_PROPERTY(quint32 size READ size STORED false CONSTANT)

public:
    enum ROLES
    {
        CELL_ROLE = Qt::UserRole + 1
    };

    Board();
    Board(QObject* parent);
    Board(SudokuSolver::Core::Board& board);
    virtual ~Board();
    quint32 size() const;
private:
    Q_DISABLE_COPY(Board)

    void initCells();

    SudokuSolver::Core::Board* _board;
    QVector< QVector<Cell*> > _cells;
    bool _cleanupBoard;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
    virtual QModelIndex parent(const QModelIndex& child) const;
    virtual int rowCount(const QModelIndex& parent) const;
    virtual int columnCount(const QModelIndex& parent) const;
    virtual QVariant data(const QModelIndex& index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
};

}}

#endif

#include "piece.h"

Piece::Piece() :
    _row(0), _col(0), _round(0), _color(Qt::transparent), _state(eNone)
{

}

Piece::Piece(int row, int col) :
    _row(row), _col(col), _round(0), _color(Qt::transparent), _state(eNone)
{

}

Piece::Piece(int row, int col, int round, QColor color) :
    _row(row), _col(col), _round(round), _color(color), _state(ePlaced)
{

}

Piece::~Piece()
{

}

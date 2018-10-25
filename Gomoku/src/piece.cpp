#include "piece.h"

Piece::Piece() :
    _row(0), _col(0), _round(0), _color(eTransparent), _state(eNone)
{

}

Piece::Piece(int row, int col) :
    _row(row), _col(col), _round(0), _color(eTransparent), _state(eNone)
{

}

Piece::Piece(int row, int col, int round, Piece::EPieceColor color) :
    _row(row), _col(col), _round(round), _color(color), _state(ePlaced)
{

}

Piece::~Piece()
{

}

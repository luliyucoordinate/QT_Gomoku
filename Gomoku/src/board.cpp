#include "board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    _isHidden(false),
    _isBlocked(false),
    _round(0),
    _pieces(0),
    _pieceColor(Piece::eWhite)
{

}

void Board::resizeEvent(QResizeEvent *event)
{

}



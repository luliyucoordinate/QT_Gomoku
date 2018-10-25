#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

Board::Board(QWidget *parent) :
    QWidget(parent),
    _isHidden(false),
    _isBlocked(false),
    _round(0),
    _pieces(0),
    _pieceColor(Qt::white)
{

}

void Board::PlacePiece(int row, int col, QColor color)
{
    if (row < 0 || col < 0 || color == Qt::transparent) return;
    _board[row][col] = Piece(row, col, ++_round, color);
    _pieceStack.push(_board[row][col]);
    update();
    if (CheckWin(row, col, color)) emit gameOver(color);
    else if (_round == pow(eBoardSize-1, 2)) emit gameOver(Qt::transparent);
}

void Board::Undo(int round)
{
    for (int i = 0; i < round && _pieceStack.size(); ++i)
    {
        Piece piece = _pieceStack.top();
        _board[piece.GetRow()][piece.GetCol()].SetState(Piece::eNone);
        _board[piece.GetRow()][piece.GetCol()].SetColor(Qt::transparent);
        _pieceStack.pop();
        _round--;
        if (piece.GetColor() == _pieceColor) _pieces--;
    }
    update();
}

void Board::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _cellWidth = std::min(width(), height())/(eBoardSize + 1)*0.95;
    _center = QPointF(width()/2, height()/2);
}

void Board::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.translate(_center);

    QPen pen(Qt::black);
    pen.setWidth(2);
    pen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pen);
    painter.setBrush(QColor(255, 255, 170));
    if (_isHidden) painter.setBrush(Qt::transparent);

    int frameWidth = (eBoardSize + 1) * _cellWidth;
    painter.drawRect(-frameWidth/2, -frameWidth/2, frameWidth, frameWidth);

    // board grid
    painter.setPen(Qt::black);
    int halfWidth = (eBoardSize - 1)/2;
    for (int i = -halfWidth; i <= halfWidth; ++i)
    {
        painter.drawLine(-halfWidth, i*_cellWidth, halfWidth, i*_cellWidth);
        painter.drawLine(i*_cellWidth, -halfWidth, i*_cellWidth, halfWidth);
    }

    // base point
    double r = _cellWidth/eBasePointSize;
    painter.setBrush(Qt::black);
    for (int i = 0; i < eBasePointSize; ++i)
    {
        painter.drawEllipse(BASE_POINT[i][0]*_cellWidth - r/2, BASE_POINT[i][1]*_cellWidth - r/2, r, r);
    }

    // pieces
    if (_isHidden) return;
    r = _cellWidth/2;
    for (int i = 0; i < eBoardSize; ++i)
    {
        for (int j = 0; j < eBoardSize; ++j)
        {
            QPointF center((i - halfWidth)*_cellWidth, (j - halfWidth)*_cellWidth);
            if (_board[i][j].GetState() != Piece::eNone)
            {
                Piece piece = _board[i][j];
                QColor color = piece.GetColor();
                if (piece.GetState() == Piece::eHover)
                {
                    color = _pieceColor;
                    color.setAlpha(150);
                }
                painter.setBrush(color);
                painter.setPen(Qt::black);
                painter.drawEllipse(center, r, r);

                if (piece.GetRound() == _round && piece.GetState() == Piece::ePlaced)
                {
                    pen.setColor(Qt::red);
                    pen.setStyle(Qt::DashLine);
                    painter.setPen(pen);
                    painter.setBrush(Qt::transparent);
                    painter.drawRect(center.x() - r, center.y() - r, r*2, r*2);
                }
            }
        }
    }
}

void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (_isBlocked)
    {
        for (int i = 0; i < eBoardSize; ++i)
        {
            for (int j = 0; j < eBoardSize; ++j)
            {
                if (_board[i][j].GetColor() == Piece::eHover)
                {
                    _board[i][j].SetColor(Piece::eNone);
                }
            }
        }
        update();
        return;
    }
    for (int i = 0; i < eBoardSize; ++i)
    {
        for (int j = 0; j < eBoardSize; ++j)
        {
            if (_board[i][j].GetColor() != Piece::ePlaced)
            {
                int halfWidth = (eBoardSize - 1)/2, r = _cellWidth/2;
                QPointF center = _center + QPointF((i - halfWidth)*_cellWidth, (j - halfWidth)*_cellWidth);
                if (sqrt(center.x() - event->x()) + sqrt(center.y() - event->y()) >= r*r)
                    _board[i][j].SetState(Piece::eNone);
                else _board[i][j].SetState(Piece::eHover);
            }
        }
    }
    update();
    return;
}

void Board::mousePressEvent(QMouseEvent *event)
{
    if (_isBlocked || event->button() != Qt::LeftButton) return;
    for (int i = 0; i < eBoardSize; ++i)
    {
        for (int j = 0; j < eBoardSize; ++j)
        {
            if (_board[i][j].GetState() == Piece::eHover)
            {
                int halfWidth = (eBoardSize - 1)/2, r = _cellWidth/2;
                QPointF center = _center + QPointF((i - halfWidth)*_cellWidth, (j - halfWidth)*_cellWidth);
                if (sqrt(center.x() - event->x()) + sqrt(center.y() - event->y()) >= r*r) continue;
                if (event->button() == Qt::LeftButton)
                {
                    _pieces++;
                    PlacePiece(i, j, _pieceColor);
                    emit piecePlaced(i, j, _pieceColor);
                    return;
                }
            }
        }
    }
}



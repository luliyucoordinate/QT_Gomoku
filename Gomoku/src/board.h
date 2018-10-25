#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QStack>
#include "piece.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    //Get member functions
    int GetPieces() const { return _pieces; }
    Piece::EPieceColor GetColor() const { return _pieceColor; }

    //Set member functions
    void SetColor(Piece::EPieceColor color) { _pieceColor = color; }
    void SetBlock(bool block) { _isBlocked = block; }
    void setHidden(bool hidden) { _isHidden = hidden; }

    void PlacePiece(int row, int col, Piece::EPieceColor color);
    void Undo(int round);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool _isHidden;
    bool _isBlocked;
    int _round;
    int _pieces;
    double _cellWidth;
    Piece::EPieceColor _pieceColor;

    QStack<Piece> _pieceStack;
    enum { eBoardSize = 15 };
    Piece _board[eBoardSize][eBoardSize];


private:
    bool _checkWin(int row, int col, Piece::EPieceColor color) const;
    bool _isOnBoard(int row, int col) const { return 0 <= row && row < eBoardSize && 0 <= col && col < eBoardSize; }
    bool _isAvaliable(int row, int col) const { return _isOnBoard(row, col) && _board[row][col].GetColor() == Piece::eTransparent; }

signals:

public slots:
};

#endif // BOARD_H

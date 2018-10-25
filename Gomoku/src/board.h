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
    QColor GetColor() const { return _pieceColor; }

    //Set member functions
    void SetColor(QColor color) { _pieceColor = color; }
    void SetBlock(bool block) { _isBlocked = block; }
    void setHidden(bool hidden) { _isHidden = hidden; }

    void PlacePiece(int row, int col, QColor color);
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
    QColor _pieceColor;
    QPointF _center;

    QStack<Piece> _pieceStack;
    enum { eBoardSize = 15 };
    Piece _board[eBoardSize][eBoardSize];

    enum { eBasePointSize = 5 };
    const int BASE_POINT[eBasePointSize][2] = {{0,0}, {4,4}, {4,-4}, {-4,4}, {-4,-4}};


private:
    bool _checkWin(int row, int col, QColor color) const;
    bool _isOnBoard(int row, int col) const { return 0 <= row && row < eBoardSize && 0 <= col && col < eBoardSize; }
    bool _isAvaliable(int row, int col) const { return _isOnBoard(row, col) && _board[row][col].GetColor() == Qt::transparent; }

signals:
    void piecePlaced(int row, int col, QColor color);
    void gameOver(QColor color);

public slots:
};

#endif // BOARD_H

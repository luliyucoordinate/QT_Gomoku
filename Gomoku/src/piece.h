#ifndef PIECE_H
#define PIECE_H
#include <QColor>

class Piece
{
public:
    enum EPieceState {eNone, eHover, ePlaced};
    explicit Piece();
    explicit Piece(int row, int col);
    explicit Piece(int row, int col, int round, QColor color);
    ~Piece();


    //Get member functions
    int GetRow() const { return _row; }
    int GetCol() const { return _col; }
    int GetRound() const { return _round; }
    QColor GetColor() const { return _color; }
    EPieceState GetState() const { return _state; }

    //Set member functions
    void SetColor(QColor color) { _color = color; }
    void SetState(EPieceState state) { _state = state; }
    void SetPosition(int row, int col) { _row = row; _col = col; }

private:
    int _row;
    int _col;
    int _round;
    QColor _color;
    EPieceState _state;
};

#endif // PIECE_H

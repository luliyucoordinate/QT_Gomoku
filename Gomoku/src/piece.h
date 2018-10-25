#ifndef PIECE_H
#define PIECE_H


class Piece
{
public:
    enum EPieceColor {eTransparent, eWhite, eBlack};
    enum EpieceState {eNone, eHover, ePlaced};
    explicit Piece();
    explicit Piece(int row, int col);
    explicit Piece(int row, int col, int round, EPieceColor color);
    ~Piece();


    //Get member functions
    int GetRow() const { return _row; }
    int GetCol() const { return _col; }
    int GetRound() const { return _round; }
    EPieceColor GetColor() const { return _color; }
    EpieceState GetState() const { return _state; }

    //Set member functions
    void Setcolor(EPieceColor color) { _color = color; }
    void SetState(EpieceState state) { _state = state; }
    void SetPosition(int row, int col) { _row = row; _col = col; }

private:
    int _row;
    int _col;
    int _round;
    EPieceColor _color;
    EpieceState _state;
};

#endif // PIECE_H

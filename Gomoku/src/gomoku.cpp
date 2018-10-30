#include "gomoku.h"
#include "ui_gomoku.h"
#include "board.h"
#include <QMessageBox>

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku),
    _mode(eSingle),
    _color(Qt::black),
    _isStarted(false),
    _isBlocked(false),
    _canUndo(false)
{
    ui->setupUi(this);
    connect(ui->board, &Board::piecePlaced, this, &Gomoku::onMove);
    connect(ui->board, &Board::gameOver, this, &Gomoku::onGameOver);
}

Gomoku::~Gomoku()
{
    delete ui;
}

void Gomoku::closeEvent(QCloseEvent *event)
{
    emit disconnected();
}

void Gomoku::SetBlock(bool isBlock)
{

}

void Gomoku::Initialize()
{
    ui->board->SetHidden(false);
}

void Gomoku::onMove(int row, int col, QColor color)
{
    switch (_mode)
    {
    case eSingle:
        if (_isStarted) return;
        ui->board->RevertColor();
        break;
    default:
        break;
    }
}

void Gomoku::onGameOver(QColor color)
{
    if (color == Qt::transparent)
        QMessageBox::information(this, tr("DRAW"), tr("hahaha..."));
    else
    {
        switch (_mode)
        {
        case eSingle:
            if (color == Qt::black)
                QMessageBox::information(this, tr("WIN!"), tr("You win the game :-)"));
            else
                QMessageBox::information(this, tr("LOSE"), tr("You lose the game :-("));
            break;
        default:
            break;
        }
    }
}

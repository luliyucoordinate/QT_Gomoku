#include "gomoku.h"
#include "ui_gomoku.h"
#include "board.h"
#include <QMessageBox>

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku),
    _mode(eSingle),
    _color(Qt::black),
    _canUndo(false)
{
    ui->setupUi(this);
    connect(ui->board, &Board::piecePlaced, this, &Gomoku::onMove);
    connect(ui->board, &Board::gameOver, this, &Gomoku::onGameOver);
    connect(&_timer, &QTimer::timeout, this, &Gomoku::onTimeOut);
    Initialize();
}

Gomoku::~Gomoku()
{
    delete ui;
}

void Gomoku::closeEvent(QCloseEvent *event)
{
    emit disconnected();
}


void Gomoku::Initialize()
{
    ui->board->SetHidden(false);
    ui->draw->setEnabled(false);
    ui->resign->setEnabled(false);
    ui->withDraw->setEnabled(false);
    ui->play1AllTimeLcd->display("00");
    ui->play1CountDownLcd->display("00");
    ui->play2AllTimeLcd->display("00");
    ui->play2CountDownLcd->display("00");
}

void Gomoku::onMove(int row, int col, QColor color)
{
    switch (_mode)
    {
    case eSingle:
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

void Gomoku::onTimeOut()
{
    _timeLeft--;
    int play1, play2;
    if ((_mode == eNetwork) ||
        (_mode == eSingle && ui->board->GetColor() == Qt::white) ||
        (_mode == eAI && ui->board->GetColor() == Qt::white))
    {

    }
}

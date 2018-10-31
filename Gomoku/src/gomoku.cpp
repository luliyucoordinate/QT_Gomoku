#include "gomoku.h"
#include "ui_gomoku.h"
#include "board.h"
#include <QMessageBox>
#include <QString>
#include <QTime>

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku),
    _mode(eSingle),
    _color(Qt::black),
    _isStart(false),
    _isBlock(false),
    _canUndo(false),
    _type(eServer),
    _currentPlayer(eServer)
{
    ui->setupUi(this);
    connect(ui->start, &QPushButton::clicked, this, &Gomoku::Start)
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

void Gomoku::SetBlock(bool isBlock)
{
    _currentPlayer = _type;
    if (isBlock) _currentPlayer = _type == eServer ? eClient : eServer;
    _isBlock = isBlock;
    ui->board->SetBlock(isBlock);
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
        play1 = ++_play1TotalTime;
        play2 = _play2TotalTime;
    }
    else
    {
        play1 = ++_play2TotalTime;
        play2 = _play1TotalTime;
    }
    QString time = QString::number(_timeLeft);
    if (_timeLeft < 10) time = "0" + time;
    if ((_mode = eNetwork) ||
        (_mode == eSingle && ui->board->GetColor() == Qt::white) ||
        (_mode == eAI && ui->board->GetColor() == Qt::white))
    {
        ui->play1AllTimeLcd->display(QTime(0,0,0).addSecs(play1).toString("mm:ss"));
        ui->play1CountDownLcd->display(time);
        ui->play2AllTimeLcd->display(QTime(0,0,0).addSecs(play2).toString("mm:ss"));
        ui->play2CountDownLcd->display(eTimeLimit);
        ui->play2CountDownLcd->setStyleSheet("");
        if (_timeLeft < 10) ui->play1CountDownLcd->setStyleSheet("color:red;");
        else ui->play1CountDownLcd->setStyleSheet("");
    }
    else
    {
        ui->play1AllTimeLcd->display(QTime(0,0,0).addSecs(play1).toString("mm:ss"));
        ui->play1CountDownLcd->display(eTimeLimit);
        ui->play1CountDownLcd->setStyleSheet("");
        ui->play2AllTimeLcd->display(QTime(0,0,0).addSecs(play2).toString("mm:ss"));
        ui->play2CountDownLcd->display(time);
        if (_timeLeft < 10) ui->play2CountDownLcd->setStyleSheet("color:red;");
        else ui->play2CountDownLcd->setStyleSheet("");
    }
    if (!_timeLeft)
    {
        _canUndo = false;
        nextMove();
    }
}

void Gomoku::start()
{
    switch (_mode) {
    case eSingle:
        _play1TotalTime = _play2TotalTime = 0;
        _timeLeft = eTimeLimit + 1;
        _timer.start(1000);
        ui->board->Clear();
        ui->board->SetColor(Qt::black);
        ui->draw->setEnabled(true);
        ui->withDraw->setEnabled(true);
        _isStart = true;
        break;
    default:
        break;
    }
}

void Gomoku::nextMove()
{
    if (_isBlock) play1Move(-1, -1, Qt::transparent);
    else play2Move(-1, -1, Qt::transparent);
}

void Gomoku::play1Move(int row, int col, QColor color)
{

}

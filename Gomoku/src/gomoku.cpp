#include "gomoku.h"
#include "ui_gomoku.h"
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

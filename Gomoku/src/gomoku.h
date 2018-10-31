#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>
#include <QColor>
#include <QTimer>

namespace Ui {
class Gomoku;
}

class Gomoku : public QMainWindow
{
    Q_OBJECT
public:
    enum EMode { eSingle, eNetwork, eAI};
    explicit Gomoku(QWidget *parent = nullptr);
    ~Gomoku();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Gomoku *ui;
    EMode _mode;
    QColor _color;
    bool _isStart;
    bool _isBlock;
    bool _canUndo;
    enum EHostType {eClient, eServer};
    EHostType _type, _currentPlayer;
    enum {eTimeLimit = 30};

    QTimer _timer;
    int _timeLeft;
    int _play1TotalTime;
    int _play2TotalTime;

private:
    void Initialize();
    void SetBlock(bool isBlock);


signals:
    void disconnected();

private slots:
    void onMove(int row, int col, QColor color);
    void onGameOver(QColor color);
    void onTimeOut();

    void start();
    void draw();
    void resign();
    void withDraw();

    void nextMove();
    void play1Move(int row, int col, QColor color);
    void play2Move(int row, int col, QColor color);
};

#endif // GOMOKU_H

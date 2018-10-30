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
    bool _canUndo;
    enum EHostType {eClient, eServer};

    QTimer _timer;
    int _timeLeft;
    int play1TotalTime;
    int play2TotalTime;

private:
    void Initialize();


signals:
    void disconnected();

private slots:
    void onMove(int row, int col, QColor color);
    void onGameOver(QColor color);
    void onTimeOut();

};

#endif // GOMOKU_H

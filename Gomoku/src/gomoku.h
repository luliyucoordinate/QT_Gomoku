#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>

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
    bool _isStarted;
    bool _isBlocked;
    bool _canUndo;
    enum EHostType {eClient, eServer};

private:
    void SetBlock(bool isBlock);
    void Initialize();


signals:
    void disconnected();

};

#endif // GOMOKU_H

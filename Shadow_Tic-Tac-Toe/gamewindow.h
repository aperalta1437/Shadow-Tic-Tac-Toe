#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStateMachine>
#include <QEventTransition>
#include <QPropertyAnimation>
class FlipCoin;
#include "shadowlist.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::GameWindow     *ui;

    QStateMachine      *machine;
    QState             *s1;
    QState             *s2;
    QPropertyAnimation *animation;
    QEventTransition   *t1;
    ShadowList         shadowListInitializer;
    bool               mayStart = false;
    int                coinFace;
    QChar              opponent;

    int                currShadowMove = 0;
    int                *shadowMovesList;

    QChar              userMark;
    QChar              opponentMark;
    int                playerTurn;

    int                board[3][3] = {{0}, {0}, {0}};
    int                shadowBoard[3][3] = {{0}, {0}, {0}};

    void makeShadowMove(QChar);
    void computerMoves();

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void setShadowMovesList(int *movesList);
    void setCoinFace(int playerNum);
    void setOpponent(QChar opponent);
    int evaluateWinner(int _board[3][3], bool isSolid);


public slots:
    void setUserMark(QChar mark);

private slots:
    void on_pushButton_36_clicked();
    void on_pushButton_38_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_14(QChar);
    void on_pushButton_16(QChar);
    void on_pushButton_15(QChar);
    void on_pushButton_13(QChar);
    void on_pushButton_12(QChar);
    void on_pushButton_11(QChar);
    void on_pushButton_35(QChar);
    void on_pushButton_17(QChar);
    void on_pushButton_10(QChar);

signals:
    void homeClicked();
};

#endif // GAMEWINDOW_H

#ifndef FLIPCOIN_H
#define FLIPCOIN_H

#include <QDialog>
#include "gamewindow.h"

namespace Ui {
class FlipCoin;
}

class FlipCoin : public QDialog
{
    Q_OBJECT

private:
    Ui::FlipCoin *ui;
    GameWindow *parentObject;
    bool wasClicked = false;
    QChar userMark = '\0';
    QChar opponentLetter;

public:
    explicit FlipCoin(GameWindow *parent = nullptr);
    ~FlipCoin();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

signals:
    void continueButtonClicked(QChar userMark);
};

#endif // FLIPCOIN_H

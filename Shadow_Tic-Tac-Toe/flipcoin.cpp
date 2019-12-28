/*
 * This class is design for the creation of a window that gathers data from the user.
 */

#include "flipcoin.h"
#include "ui_flipcoin.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <QDebug>

FlipCoin::FlipCoin(GameWindow *parent) :
    QDialog(parent),                            // Inherit from QDialog to gets its methods.
    ui(new Ui::FlipCoin)
{
    ui->setupUi(this);
    parentObject = parent;                      // Create a reference to the parent window of this class.
    ui->stackedWidget->setCurrentIndex(0);      // Set the current scene to 0 (first scene).
    // Create a connection between the a signal of this class and a slot of this class that gets triggered when the user has chosen his/her mark.
    connect(this, SIGNAL(continueButtonClicked(QChar)), parent, SLOT(setUserMark(QChar)));

    ui->checkBox->setChecked(true);
}

FlipCoin::~FlipCoin()
{
    delete ui;
}

/*
 * If the user chooses to close the game, a question window will pop up to make sure that is the user's wish.
 */
void FlipCoin::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Question",
                          "Cancelling will close the application\nAre you sure you want to proceed?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

/*
 * When the button correponding to this function gets clicked a random number from 1 to 2 will be
 * generated to determine who will nhave the first turn. The button then changes action and leads
 * the user to the next scene within the window when clicked by a second time to proceed with the game.
 */
void FlipCoin::on_pushButton_clicked()
{
    if(!wasClicked) {
        srand(time(0));
        int coinFace = (rand() % (2 - 1 + 1)) + 1;

        if(coinFace == 1) {
            ui->label_2->setText("The number generated is 1,\nWhich means that you play first.");
        }
        else {
            ui->label_2->setText("The number generated is 2,\nWhich means that you play second.");
        }
        parentObject->setCoinFace(coinFace);
        wasClicked = true;
        ui->pushButton->setText("Continue");
    }
    else {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

/*
 * If the user presses this button he/she would select the symbol "X" as his/her mark.
 */
void FlipCoin::on_pushButton_5_clicked()
{
    ui->label_4->setText("\"X\" was selected as your mark.");
    userMark = 'X';
}

/*
 * If the user presses this button he/she would select the symbol "O" as his/her mark.
 */
void FlipCoin::on_pushButton_6_clicked()
{
    ui->label_4->setText("\"O\" was selected as your mark.");
    userMark = 'O';
}

/*
 * If this button gets pressed, the user will be asked whether he/she wants to close the game or not.
 */
void FlipCoin::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Question",
                          "Cancelling will close the application\nAre you sure you want to proceed?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

/*
 *  When pressed a signal will be sent to the game window to determine the user's mark
 *  and the current window will be closed to start the game.
 */
void FlipCoin::on_pushButton_4_clicked()
{
    if(userMark != '\0') {
        emit continueButtonClicked(userMark);
        ui->stackedWidget->setCurrentIndex(2);
    }
}



void FlipCoin::on_checkBox_stateChanged(int arg1)
{
    ui->checkBox_2->setChecked(!arg1);
    opponentLetter = 'C';
}

void FlipCoin::on_checkBox_2_stateChanged(int arg1)
{
    ui->checkBox->setChecked(!arg1);
    opponentLetter = 'U';
}

void FlipCoin::on_pushButton_7_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Question",
                          "Cancelling will close the application\nAre you sure you want to proceed?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void FlipCoin::on_pushButton_8_clicked()
{
    parentObject->setOpponent(opponentLetter);
    this->close();
}

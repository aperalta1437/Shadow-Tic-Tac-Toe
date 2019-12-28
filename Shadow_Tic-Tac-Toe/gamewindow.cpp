#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>          // To give messages to the user through pop-up windows.
#include <QDebug>               // This header was used for debugging purposes.

/* ATTENTION:
 * All the code written here, except for the minimax algorithm was created by
 * Angel Peralta. I used this algorithm with the intention of giving the user
 * a better experience by making the computer's moves smarter.
 *
 * Link to the page where I found the algorithm is here:
 * https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
 *
 * However, that algorithm has errors, so I took the python equivalent for guidance. The python algorithm
 * can be found at:
 * https://ide.geeksforgeeks.org/KTAN36
 */

// Holds the corresponding row and column number of a movement.
struct Move
{
    int row, col;
};

/*
 * The isMovesLeft returns true if there are movements left within the given board.
 * Otherwise, returns false.
 */
bool isMovesLeft(int _board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (_board[i][j] == 0)
            {
                    return true;
            }
        }
    }
    return false;
}

/*
 * The evaluate function evaluates the given board for wins losses and neither.
 */
int evaluate(int _board[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (_board[row][0] == _board[row][1] &&
            _board[row][1] == _board[row][2])
        {
            if (_board[row][0] == 1)
            {
                return 10;
            }
            else if (_board[row][0] == 2)
            {
                return -10;

            }
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (_board[0][col] == _board[1][col] &&
            _board[1][col] == _board[2][col])
        {
            if (_board[0][col] == 1)
            {
                return 10;
            }

            else if (_board[0][col] == 2)
            {
                return -10;
            }
        }
    }

    // Checking for Diagonals for X or O victory.
    if (_board[0][0] == _board[1][1] && _board[1][1] == _board[2][2])
    {
        if (_board[0][0] == 1)
        {
            return 10;
        }
        else if (_board[0][0] == 2)
        {
            return -10;
        }
    }

    if (_board[0][2] == _board[1][1] && _board[1][1] == _board[2][0])
    {
        if (_board[0][2] == 1)
        {
            return 10;
        }
        else if (_board[0][2] == 2)
        {
            return -10;
        }
    }

    // Else if none of them have won then return 0
    return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board.
int minimax(int _board[3][3], int depth, bool isMax)
{
    int score = evaluate(_board);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score - depth;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score - depth;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(_board) == false)
        return 0 - depth;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (_board[i][j] == 0)
                {
                    // Make the move
                    _board[i][j] = 1;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = qMax( best,
                        minimax(_board, depth+1, !isMax) );

                    // Undo the move
                    _board[i][j] = 0;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (_board[i][j] == 0)
                {
                    // Make the move
                    _board[i][j] = 2;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = qMin(best,
                           minimax(_board, depth+1, !isMax));

                    // Undo the move
                    _board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

// This will return the best possible move for the player
Move findBestMove(int _board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (_board[i][j] == 0)
            {
                // Make the move
                _board[i][j] = 1;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(_board, 0, false);

                // Undo the move
                _board[i][j] = 0;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}



GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->gridLayout->setSpacing(0);              // Set the spacing of the solid board's grid to 0.
    ui->gridLayout_2->setSpacing(0);            // Set the spacing of the shadow board's grid to 0.

    ui->label_2->hide();                        // TO-DO Update of state is required once the user is able to ask for another round. Therefore, the label was hidden from the user.
    ui->label_3->hide();                        // TO-DO Update of state is required once the user is able to ask for another round. Therefore, the label was hidden from the user.
    ui->label_4->hide();                        // Hide the label that's responsable for showing whose turn to play.
    shadowListInitializer.start();              // Start the shadow board's movements initializer in a separate thread.

    machine = new QStateMachine(this);          // Create a new QStateMachine object to set the animations settings.

    // Create the first state of the blanket object and assign the initial geometry property to it.
    s1 = new QState();
    s1->assignProperty(ui->blanket, "geametry", QRect(510, 10, 481, 16));

    // Create the second state of the blanket objet and assign the final geometry property to it.
    s2 = new QState();
    s2->assignProperty(ui->blanket, "geometry", QRect(510, 10, 481, 481));

    // Create animation.
    animation = new QPropertyAnimation(ui->blanket, "geometry");
    animation->setEasingCurve(QEasingCurve::OutBounce);


    // Adding Event Transition to the code.
    t1 = new QEventTransition(ui->pushButton_38, QEvent::MouseButtonPress);     // Link the change of state to the "Start" button or pushButton_38 object.
    t1->setTargetState(s2);
    t1->addAnimation(animation);
    s1->addTransition(t1);

    // Add the two previously created states to the QStateMahine object previously created.
    machine->addState(s1);
    machine->addState(s2);

    machine->setInitialState(s1);           // Set the initial state of object.
    machine->start();                       // Implementent the transitioning process.


}

GameWindow::~GameWindow()
{
    delete ui;
}

/* The setShadowMovesList sets the list of moves for the shadow board.
 */
void GameWindow::setShadowMovesList(int *movesList)
{
    shadowMovesList = movesList;
}

/* The setCoinFace function sets the coin's face to either 1 or 2
 * in order to determine the first player.
 */
void GameWindow::setCoinFace(int playerNum)
{
    coinFace = playerNum;
}

/* The setOpponent function sets the opponent's initial to
 * either C for Computer or U for User.
 */
void GameWindow::setOpponent(QChar opponentLetter)
{
    opponent = opponentLetter;
}

/*
 * Prompt the user to answer whether he/she wants to quit the game.
 */
void GameWindow::on_pushButton_36_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Question",
                          "Quitting the game will close the application.\nAre you sure you want to proceed?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

/*
 * Starts the game and allows the first player to play.
 */
void GameWindow::on_pushButton_38_clicked()
{
    if(!mayStart) {
        ui->label->hide();
        shadowMovesList = shadowListInitializer.getShadowMovesList();
        mayStart = true;

        if(coinFace == 2 && opponent == 'C') {                      // If opponent plays first and opponent is the computer.
            playerTurn = 2;
            computerMoves();
        }
        else if(coinFace == 2 && opponent == 'U') {
            ui->label_4->show();
            ui->label_4->setText("Player's turn: 2nd User");        // Let the user know whose turn is it.
            playerTurn = 2;
        }
        else if(coinFace == 1 && opponent == 'U') {
            ui->label_4->show();
            ui->label_4->setText("Player's turn: 1st User");        // Let the user know whose turn is it.
            playerTurn = 1;
        }
        else {
            playerTurn = 1;
        }

        ui->pushButton_38->setText("New game");
    }
    else {

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Question",
                              "You will only be able to re-start the game once.\nAre you sure you want to proceed?",
                              QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) {
            emit homeClicked();
        }
    }
}

/* Makes a move in the box 1:1 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_5_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_5->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_5->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[0][0] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);

        playerTurn = (playerTurn == 1) ? 2 : 1;

        if(opponent == 'C' && playerTurn == 2) {
            computerMoves();
        }

        if(opponent == 'U') {
            (playerTurn == 1) ? ui->label_4->setText("Player's turn: 1st User") : ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 1:2 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_7_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_7->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_7->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[0][1] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);

        playerTurn = (playerTurn == 1) ? 2 : 1;

        if(opponent == 'C' && playerTurn == 2) {
            computerMoves();
        }

        if(opponent == 'U') {
            (playerTurn == 1) ? ui->label_4->setText("Player's turn: 1st User") : ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 1:3 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_6_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_6->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_6->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[0][2] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 2:1 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_4_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_4->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_4->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[1][0] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 2:2 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_2_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_2->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_2->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[1][1] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 2:3 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton->setEnabled(false);                          // Disable the box from further player's interaction.
        ui->pushButton->setText(mark);                              // Set the text within the box equals to the player's mark.
        board[1][2] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 3:1 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_8_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_8->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_8->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[2][0] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 3:2 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_3_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_3->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_3->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[2][1] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* Makes a move in the box 3:3 of the solid board.
 * This function also makes a move within the shadow board.
 */
void GameWindow::on_pushButton_9_clicked()
{
    if (mayStart) {
        QChar mark = (playerTurn == 1) ? userMark : opponentMark;    // Determine the player's mark based on who called the function.
        ui->pushButton_9->setEnabled(false);                        // Disable the box from further player's interaction.
        ui->pushButton_9->setText(mark);                            // Set the text within the box equals to the player's mark.
        board[2][2] = playerTurn;                                    // Make the corresponding move within the 2D Arrays that corresponds to the solid board.
        makeShadowMove(mark);                                       // Make a random player's move on the shadow board.

        playerTurn = (playerTurn == 1) ? 2 : 1;     // If it is user's turn, chenge to opponent's turn and viceversa.

        if(opponent == 'C' && playerTurn == 2) {    // If the opponent is the computer and is the computer's turn.
            computerMoves();                        // Let computer move.
        }

        if(opponent == 'U') {                       // If the opponent is a second user.
            (playerTurn == 1) ?                     // Let the user know whose turn is it.
                        ui->label_4->setText("Player's turn: 1st User") :
                        ui->label_4->setText("Player's turn: 2nd User");
        }
    }
}

/* The makeShadowMove function takes the player's mark as a parameter
 * and makes a random move based on a given number within the range of 0 thorugh 8
 * on the shadow board.
 */
void GameWindow::makeShadowMove(QChar mark) {

    switch (shadowMovesList[currShadowMove]) {

        case 0:
            on_pushButton_14(mark);
            (mark == userMark) ? shadowBoard[0][0] = 1 : shadowBoard[0][0] = 2;
        break;
        case 1:
            on_pushButton_16(mark);
            (mark == userMark) ? shadowBoard[0][1] = 1 : shadowBoard[0][1] = 2;
        break;
        case 2:
            on_pushButton_15(mark);
            (mark == userMark) ? shadowBoard[0][2] = 1 : shadowBoard[0][2] = 2;
        break;
        case 3:
            on_pushButton_13(mark);
            (mark == userMark) ? shadowBoard[1][0] = 1 : shadowBoard[1][0] = 2;
        break;
        case 4:
            on_pushButton_12(mark);
            (mark == userMark) ? shadowBoard[1][1] = 1 : shadowBoard[1][1] = 2;
        break;
        case 5:
            on_pushButton_11(mark);
            (mark == userMark) ? shadowBoard[1][2] = 1 : shadowBoard[1][2] = 2;
        break;
        case 6:
            on_pushButton_35(mark);
            (mark == userMark) ? shadowBoard[2][0] = 1 : shadowBoard[2][0] = 2;
        break;
        case 7:
            on_pushButton_17(mark);
            (mark == userMark) ? shadowBoard[2][1] = 1 : shadowBoard[2][1] = 2;
        break;
        case 8:
            on_pushButton_10(mark);
            (mark == userMark) ? shadowBoard[2][2] = 1 : shadowBoard[2][2] = 2;
        break;
    }

    currShadowMove++;       // Increment currShadowMove by one so a different box number gets selected the next time this function gets called.

    int solidResult = evaluateWinner(board, true);              // Evealuate the solid board to find whether it is a win, a loss, a tie or none of them.
    int shadowResult = evaluateWinner(shadowBoard, false);      // Evealuate the shadow board to find whether it is a win, a loss, a tie or none of them.

    int result = (solidResult == 0 || solidResult == 3) ? ((shadowResult != 0) ? shadowResult: solidResult) : solidResult;      // Evealuate the previous results to determine the final result.

    // Let the user know what is going on based on the result.
    if(result == 1)
    {
        ui->blanket->hide();
        if(opponent == 'C') {
            QMessageBox::information(this, "Winner",
                                    "You have won the game!");
        }
        else {
            QMessageBox::information(this, "Winner",
                                    "1st User has won the game!");
        }

        QApplication::quit();
    }
    else if(result == 2)
    {
        ui->blanket->hide();
        if(opponent == 'C') {
            QMessageBox::information(this, "Winner",
                                    "You have lost the game!");
        }
        else {
            QMessageBox::information(this, "Winner",
                                    "2nd User has won the game!");
        }

        QApplication::quit();
    }
    else if(result == 3)
    {
        ui->blanket->hide();
        QMessageBox::information(this, "Winner",
                                "The game resulted in a tie.");

        QApplication::quit();
    }
}

/* Places the user's mark in the box 1:1 of the shadow board.
 */
void GameWindow::on_pushButton_14(QChar mark)
{
    ui->pushButton_14->setText(mark);
}

/* Places the user's mark in the box 1:2 of the shadow board.
 */
void GameWindow::on_pushButton_16(QChar mark)
{
    ui->pushButton_16->setText(mark);
}

/* Places the user's mark in the box 1:3 of the shadow board.
 */
void GameWindow::on_pushButton_15(QChar mark)
{
    ui->pushButton_15->setText(mark);
}

/* Places the user's mark in the box 2:1 of the shadow board.
 */
void GameWindow::on_pushButton_13(QChar mark)
{
    ui->pushButton_13->setText(mark);
}

/* Places the user's mark in the box 2:2 of the shadow board.
 */
void GameWindow::on_pushButton_12(QChar mark)
{
    ui->pushButton_12->setText(mark);
}

/* Places the user's mark in the box 2:3 of the shadow board.
 */
void GameWindow::on_pushButton_11(QChar mark)
{
    ui->pushButton_11->setText(mark);
}

/* Places the user's mark in the box 3:1 of the shadow board.
 */
void GameWindow::on_pushButton_35(QChar mark)
{
    ui->pushButton_35->setText(mark);
}

/* Places the user's mark in the box 3:2 of the shadow board.
 */
void GameWindow::on_pushButton_17(QChar mark)
{
    ui->pushButton_17->setText(mark);
}

/* Places the user's mark in the box 3:3 of the shadow board.
 */
void GameWindow::on_pushButton_10(QChar mark)
{
    ui->pushButton_10->setText(mark);
}

/* Sets the user and computer's marks.
 */
void GameWindow::setUserMark(QChar mark)
{
    userMark = mark;
    opponentMark = (userMark == 'X') ? 'O' : 'X';
}

/* Makes the computer's move on the solid board based on the Minimax algorithm.
 */
void GameWindow::computerMoves() {
    Move bestMove = findBestMove(board);        // Find the best movement for the computer.

    // These nested switch statements make the computer's move based on the previous given results.
    switch(bestMove.row) {
        case 0:
            switch (bestMove.col) {
                case 0:
                    on_pushButton_5_clicked();
                break;
                case 1:
                    on_pushButton_7_clicked();
                break;
                case 2:
                    on_pushButton_6_clicked();
                break;
            }
        break;
        case 1:
        switch (bestMove.col) {
            case 0:
                on_pushButton_4_clicked();
            break;
            case 1:
                on_pushButton_2_clicked();
            break;
            case 2:
                on_pushButton_clicked();
            break;
        }
        break;
        case 2:
        switch (bestMove.col) {
            case 0:
                on_pushButton_8_clicked();
            break;
            case 1:
                on_pushButton_3_clicked();
            break;
            case 2:
                on_pushButton_9_clicked();
            break;
        }
        break;
    }
}

/* The evealuateWinner function evaluates the board to determine whether
 * there is a winner or not.
 */
int GameWindow::evaluateWinner(int _board[3][3], bool isSolid)
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (_board[row][0] == _board[row][1] &&
            _board[row][1] == _board[row][2])
        {
            if (_board[row][0] == 1)
            {
                return 1;
            }
            else if (_board[row][0] == 2)
            {
                return 2;
            }

            if(isSolid)
            {

            }
            else
            {

            }
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (_board[0][col] == _board[1][col] &&
            _board[1][col] == _board[2][col])
        {
            if (_board[0][col] == 1)
            {
                return 1;
            }

            else if (_board[0][col] == 2)
            {
                return 2;
            }

            if(isSolid)
            {

            }
            else
            {

            }
        }
    }

    // Checking for Diagonals for X or O victory.
    if (_board[0][0] == _board[1][1] && _board[1][1] == _board[2][2])
    {
        if (_board[0][0] == 1)
        {     
            return 1;
        }
        else if (_board[0][0] == 2)
        {
            return 2;
        }

        if(isSolid)
        {

        }
        else
        {

        }
    }

    if (_board[0][2] == _board[1][1] && _board[1][1] == _board[2][0])
    {
        if (_board[0][2] == 1)
        {
            return 1;
        }
        else if (_board[0][2] == 2)
        {
            return 2;
        }

        if(isSolid)
        {

        }
        else
        {

        }
    }

    if(!isMovesLeft(_board))
    {
        return 3;
    }

    return 0;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <flipcoin.h>

MainWindow::MainWindow(QWidget *parent)     // parent corresponds to the parent window of any instance of this class.
    : QMainWindow(parent),                  // Inherit from QMainWindow to get its methods.
      ui(new Ui::MainWindow),               // Instantiate an Ui object for the MainWindow class.
      gameWindow(new GameWindow)            // Instantiate a GameWindow object to create the next scene of the game.
{
    ui->setupUi(this);                      // Link the Ui to current instance of this class.
    ui->stackedWidget->addWidget(gameWindow);// Add the GameWindow object to the stackedWidget structure.
    ui->pushButton_2->hide();                // TO-DO An action is required on this button and therefore it has been hidden from the user.
    connect(gameWindow, SIGNAL(homeClicked()), this, SLOT(moveHome())); // Create a connection between a signal in the game window and a slot within this object.
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameWindow;
}


/*
 * Closes the main window closing the game if the the button corresponding to the pushButton object gets clicked.
 */
void MainWindow::on_pushButton_clicked()
{
    this->close();
}

/*
 * Initiates the game window if the button corresponding to pushButton_1 gets clicked.
 */
void MainWindow::on_pushButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    numberGenerator = new FlipCoin(gameWindow);
    numberGenerator->setModal(true);
    numberGenerator->exec();
}

/* This private Slot creates a new game window for a new game.
 */
void MainWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
    delete gameWindow;
    gameWindow = new GameWindow();
    ui->stackedWidget->insertWidget(1, gameWindow);
    on_pushButton_1_clicked();
}


#include "mainwindow.h"     // Including the MainWindow header file for further declaration.

#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);                 // Instantiate a QAppliaction object create an application using the Qt Framework.
    MainWindow *mainFrame = new MainWindow;            // Allocate a MainWindow object to create the main window of the application.
    mainFrame->setWindowTitle("Shadow Tic-Tac-Toe");    // Set the title of the main window.
    mainFrame->show();                                  // Call the show method of the main window to display the interface.
    return a.exec();                                    // Execute the arguments within the main method to jump start the application.
}

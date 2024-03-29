#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamewindow.h"

#include <QMainWindow>
#include "gamewindow.h"
#include "flipcoin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    GameWindow *gameWindow;
    FlipCoin *numberGenerator;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void moveHome();
};
#endif // MAINWINDOW_H

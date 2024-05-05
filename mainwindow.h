#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "chessboard.h"
#include "qpushbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton* getButton(int buttonNumber);
    QPushButton* getButton(std::pair<int, int> coordinates);
    void setBoxColor(QPushButton* boutton);
    void highlightArray(QPushButton* button, const std::vector<std::pair<int, int>> liste);
    std::pair<int, int> getCoordinate(QPushButton *clickedButton);
    void resetBoard();
    void onButtonClicked();

private:
    Ui::MainWindow *ui;
    bool isFirstClick = true;
    std::vector<std::pair<int, int>> highlights_;

};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton* MainWindow::getButton(int buttonNumber){
    return (buttonNumber >= 1 && buttonNumber <= 64) ? findChild<QPushButton *>("pushButton_"+QVariant(buttonNumber).toString()) : nullptr;
}

QPushButton* MainWindow::getButton(std::pair<int, int> coordinates){
    int ligne = coordinates.first;
    int colonne = coordinates.second;
    return ((ligne >= 0 && ligne <= 7) && (colonne >= 0 && colonne <= 7)) ? findChild<QPushButton *>("pushButton_"+QVariant((ligne)*8+colonne+1).toString()) : nullptr;
}

std::pair<int, int> MainWindow::getCoordinate(QPushButton *clickedButton){
    QString buttonName = clickedButton->objectName();
    int posNumber = buttonName.lastIndexOf("_") + 1;
    int buttonNumber = buttonName.mid(posNumber).toInt() - 1;

    int row = buttonNumber/8;
    int column = buttonNumber%8;

    return {row, column};
}

void MainWindow::setBoxColor(QPushButton* boutton){
    int ligne = getCoordinate(boutton).first;
    int colonne = getCoordinate(boutton).second;

    if (ligne%2 == 1){
        if (colonne%2 == 1){
            boutton->setStyleSheet("background-color: #bdb9a2;");
        }
        else {
            boutton->setStyleSheet("background-color: #565452;");
        }
    }
    else {
        if (colonne%2 == 0){
            boutton->setStyleSheet("background-color: #bdb9a2;");
        }
        else {
            boutton->setStyleSheet("background-color: #565452;");
        }
    }
}

void MainWindow::resetBoard(){
    for(int ligne = 1; ligne <= 8; ++ligne){
        for(int colonne = 1; colonne <= 8; ++colonne){
            QPushButton* boutton = getButton((ligne - 1)*8+colonne);

            connect(boutton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
            boutton->setText(QString(""));

            setBoxColor(boutton);
        }
    }
}

void MainWindow::highlightArray(QPushButton* button, const std::vector<std::pair<int, int>> liste){
    for(std::pair<int, int> deplacement : liste){
        getButton({getCoordinate(button).first + deplacement.first, getCoordinate(button).second + deplacement.second})->setStyleSheet("background-color: #f7f57e;");
        highlights_.push_back({getCoordinate(button).first + deplacement.first, getCoordinate(button).second + deplacement.second});
    }
}

void MainWindow::onButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {

        if (isFirstClick){
            highlightArray(clickedButton, KnightMovements);
            isFirstClick = false;
        }

        else {
             for (std::pair<int, int> coordinates : highlights_){
                setBoxColor(getButton(coordinates));
             }
            highlights_ = {};
            isFirstClick = true;
        }

        // qDebug() << "ligne = " << row ;
        // qDebug() << "colonne = " << column << endl ;
    }
}

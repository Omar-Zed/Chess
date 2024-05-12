#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, ChessBoard* plateau)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), plateau_(plateau)
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
            boutton->setFont(QFont("Arial", 60));
            boutton->setText(QString(getCharButton(boutton)));

            setBoxColor(boutton);
        }
    }
    QPushButton* boutton = findChild<QPushButton *>("pushButton");
    connect(boutton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    updateLabel();
}

QChar MainWindow::getCharButton(QPushButton *button) {
    std::pair<int, int> coordonnees = getCoordinate(button);
    switch (plateau_->getPieceAt(coordonnees)->getPieceType()) {
    case TypePiece::Vide:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0) : QChar(0);
        break;
    case TypePiece::Cavalier:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0x2658) : QChar(0x265E);
        break;
    case TypePiece::Fou:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0x2657) : QChar(0x265D);
        break;
    case TypePiece::Pion:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0x2659) : QChar(0x265F);
        break;
    case TypePiece::Reine:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0x2655) : QChar(0x265B);
        break;
    case TypePiece::Roi:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0x2654) : QChar(0x265A);
        break;
    case TypePiece::Tour:
        return (plateau_->getPieceAt(coordonnees)->getPieceCouleur() == Couleur::Blanc) ? QChar(0x2656) : QChar(0x265C);
        break;
    default:
        return QChar(0);
        break;
    }
}

QChar MainWindow::getCharType(TypePiece type, Couleur couleur){
    switch (type) {
    case TypePiece::Vide:
        return (couleur == Couleur::Blanc) ? QChar(0) : QChar(0);
        break;
    case TypePiece::Cavalier:
        return (couleur == Couleur::Blanc) ? QChar(0x2658) : QChar(0x265E);
        break;
    case TypePiece::Fou:
        return (couleur == Couleur::Blanc) ? QChar(0x2657) : QChar(0x265D);
        break;
    case TypePiece::Pion:
        return (couleur == Couleur::Blanc) ? QChar(0x2659) : QChar(0x265F);
        break;
    case TypePiece::Reine:
        return (couleur == Couleur::Blanc) ? QChar(0x2655) : QChar(0x265B);
        break;
    case TypePiece::Roi:
        return (couleur == Couleur::Blanc) ? QChar(0x2654) : QChar(0x265A);
        break;
    case TypePiece::Tour:
        return (couleur == Couleur::Blanc) ? QChar(0x2656) : QChar(0x265C);
        break;
    default:
        return QChar(0);
        break;
    }
}

void MainWindow::updateBoard(){
    for(int ligne = 1; ligne <= 8; ++ligne){
        for(int colonne = 1; colonne <= 8; ++colonne){
            QPushButton* boutton = getButton((ligne - 1)*8+colonne);
            boutton->setText(QString(getCharButton(boutton)));
        }
    }
}

void MainWindow::updateLabel(){
    QLabel* labelJoueurEnCours = findChild<QLabel*>("label_6");
    QLabel* labelPiecesNoiresCapturees = findChild<QLabel*>("label_7");
    QLabel* labelPiecesBlanchesCapturees = findChild<QLabel*>("label_11");
    QString piecesCaptureesNoires = "Pieces Noires Capturées : \n";
    QString piecesCaptureesBlanches= "Pieces Blanches Capturées : \n";
    if (labelJoueurEnCours){
        plateau_->getCurrentPlayer() == Couleur::Blanc ? labelJoueurEnCours->setText("Tour Joueur Blanc") : labelJoueurEnCours->setText("Tour Joueur Noir");
    }
    for (TypePiece type : plateau_->getPiecesCaptureesBlanc()){
        piecesCaptureesBlanches += getCharType(type, Couleur::Blanc);
    }
    for (TypePiece type : plateau_->getPiecesCaptureesNoir()){
        piecesCaptureesNoires += getCharType(type, Couleur::Noir);
    }
    labelPiecesBlanchesCapturees->setText(piecesCaptureesBlanches);
    labelPiecesNoiresCapturees->setText(piecesCaptureesNoires);
}

void MainWindow::highlightArray(QPushButton* button, const std::vector<std::pair<int, int>> &liste){
    for(std::pair<int, int> deplacement : liste){
        QPushButton* button = getButton(deplacement);
        button->setStyleSheet("background-color: #f7f57e;");
        highlights_.push_back(deplacement);
    }
}

void MainWindow::onButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        if (clickedButton->objectName() == QString("pushButton")){
            //restart
            plateau_->resetChessBoard();
            updateLabel();
        }
        else {
            Piece* pieceCliquee = plateau_->getPieceAt(getCoordinate(clickedButton));
            if (isFirstClick && pieceCliquee->getPieceType() != TypePiece::Vide && pieceCliquee->getPieceCouleur() == plateau_->getCurrentPlayer()){
                highlightArray(clickedButton, plateau_->getPieceAt(getCoordinate(clickedButton))->getMouvementsPossibles());
                isFirstClick = false;
                lastPushedButton = clickedButton;
            }

            else {
                if (lastPushedButton){
                    plateau_->moveTo(getCoordinate(lastPushedButton), getCoordinate(clickedButton));
                    for (std::pair<int, int> coordinates : highlights_){
                        setBoxColor(getButton(coordinates));
                    }
                    highlights_ = {};
                    isFirstClick = true;
                    lastPushedButton = nullptr;
                }
            }
            updateLabel();
            if (plateau_->isCheckMate(Couleur::Blanc)){
                std::cout << "Blanc Echec et Mat" << std::endl;
                plateau_->resetChessBoard();
                findChild<QLabel*>("label_6")->setText("Blanc Echec et Mat");


            }
            else if (plateau_->isCheckMate(Couleur::Noir)){
                std::cout << "Noir Echec et Mat" << std::endl;
                plateau_->resetChessBoard();
                findChild<QLabel*>("label_6")->setText("Noir Echec et Mat");
            }
        }
        updateBoard();
    }
}

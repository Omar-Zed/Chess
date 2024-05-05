#include "chessboard.h"

ChessBoard::ChessBoard() {
    // plateau_[0][0] = new Tour(Couleur::Noir, {0, 0}, this);
    // plateau_[0][1] = new Cavalier(Couleur::Noir, {0, 1}, this);
    // plateau_[0][2] = new Fou(Couleur::Noir, {0, 2}, this);
    // plateau_[0][3] = new Reine(Couleur::Noir, {0, 3}, this);
    // plateau_[0][4] = new Roi(Couleur::Noir, {0, 4}, this);
    // plateau_[0][5] = new Fou(Couleur::Noir, {0, 5}, this);
    // plateau_[0][6] = new Cavalier(Couleur::Noir, {0, 6}, this);
    // plateau_[0][7] = new Tour(Couleur::Noir, {0, 7}, this);
    // for (int colonne = 0; colonne < 8; colonne++) {
    //     plateau_[1][colonne] = new Pion(Couleur::Noir, {1, colonne}, this);
    // }

    // for (int ligne = 2; ligne < 6; ligne++) {
    //     for (int colonne = 0; colonne < 8; colonne++) {
    //         plateau_[ligne][colonne] = new Piece(this);
    //     }
    // }

    // plateau_[7][0] = new Tour(Couleur::Blanc, {7, 0}, this);
    // plateau_[7][1] = new Cavalier(Couleur::Blanc, {7, 1}, this);
    // plateau_[7][2] = new Fou(Couleur::Blanc, {7, 2}, this);
    // plateau_[7][3] = new Reine(Couleur::Blanc, {7, 3}, this);
    // plateau_[7][4] = new Roi(Couleur::Blanc, {7, 4}, this);
    // plateau_[7][5] = new Fou(Couleur::Blanc, {7, 5}, this);
    // plateau_[7][6] = new Cavalier(Couleur::Blanc, {7, 6}, this);
    // plateau_[7][7] = new Tour(Couleur::Blanc, {7, 7}, this);
    // for (int colonne = 0; colonne < 8; colonne++) {
    //     plateau_[6][colonne] = new Pion(Couleur::Blanc, {6, colonne}, this);
    // }

    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            plateau_[ligne][colonne] = new Piece(this);
        }
    }
    delete plateau_[3][5];
    plateau_[3][5] = new Pion(Couleur::Noir, {3, 5}, this);

    delete plateau_[4][4];
    plateau_[4][4] = new Pion(Couleur::Blanc, {4, 4}, this);

    delete plateau_[4][6];
    plateau_[4][6] = new Pion(Couleur::Noir, {4, 6}, this);

    delete plateau_[1][2];
    plateau_[1][2] = new Pion(Couleur::Noir, {1, 2}, this);

    delete plateau_[2][3];
    plateau_[2][3] = new Pion(Couleur::Blanc, {2, 3}, this);

    // delete plateau_[3][5];
    // plateau_[3][5] = new Fou(Couleur::Blanc, {3, 5}, this);

    // delete plateau_[3][5];
    // plateau_[3][5] = new Fou(Couleur::Blanc, {3, 5}, this);
}

std::string stringPieceType(Piece* piece){
    switch (piece->getPieceType()) {
    case TypePiece::Vide:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "VideB" : "VideN";
        break;
    case TypePiece::Cavalier:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "CavalierB" : "CavalierN";
        break;
    case TypePiece::Fou:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "FouB" : "FouN";
        break;
    case TypePiece::Pion:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "PionB" : "PionN";
        break;
    case TypePiece::Reine:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "ReineB" : "ReineN";
        break;
    case TypePiece::Roi:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "RoiB" : "RoiN";
        break;
    case TypePiece::Tour:
        return (piece->getPieceCouleur() == Couleur::Blanc) ? "TourB" : "TourN";
        break;
    default:
        return "";
        break;
    }
}

void ChessBoard::debugChessBoard(){
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            if (colonne%8 == 7){
                std::cout << stringPieceType(plateau_[ligne][colonne]) << std::endl;
            }
            else {
                std::cout << stringPieceType(plateau_[ligne][colonne]) << "   ";
            }
        }
    }
}

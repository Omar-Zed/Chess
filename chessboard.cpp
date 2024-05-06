#include "chessboard.h"
#include <algorithm>

ChessBoard::ChessBoard() {
    plateau_[0][0] = new Tour(Couleur::Noir, {0, 0}, this);
    plateau_[0][1] = new Cavalier(Couleur::Noir, {0, 1}, this);
    plateau_[0][2] = new Fou(Couleur::Noir, {0, 2}, this);
    plateau_[0][3] = new Reine(Couleur::Noir, {0, 3}, this);
    plateau_[0][4] = new Roi(Couleur::Noir, {0, 4}, this);
    plateau_[0][5] = new Fou(Couleur::Noir, {0, 5}, this);
    plateau_[0][6] = new Cavalier(Couleur::Noir, {0, 6}, this);
    plateau_[0][7] = new Tour(Couleur::Noir, {0, 7}, this);
    for (int colonne = 0; colonne < 8; colonne++) {
        plateau_[1][colonne] = new Pion(Couleur::Noir, {1, colonne}, this);
    }

    for (int ligne = 2; ligne < 6; ligne++) {
        for (int colonne = 0; colonne < 8; colonne++) {
            plateau_[ligne][colonne] = new Piece(this);
        }
    }

    plateau_[7][0] = new Tour(Couleur::Blanc, {7, 0}, this);
    plateau_[7][1] = new Cavalier(Couleur::Blanc, {7, 1}, this);
    plateau_[7][2] = new Fou(Couleur::Blanc, {7, 2}, this);
    plateau_[7][3] = new Reine(Couleur::Blanc, {7, 3}, this);
    plateau_[7][4] = new Roi(Couleur::Blanc, {7, 4}, this);
    plateau_[7][5] = new Fou(Couleur::Blanc, {7, 5}, this);
    plateau_[7][6] = new Cavalier(Couleur::Blanc, {7, 6}, this);
    plateau_[7][7] = new Tour(Couleur::Blanc, {7, 7}, this);
    for (int colonne = 0; colonne < 8; colonne++) {
        plateau_[6][colonne] = new Pion(Couleur::Blanc, {6, colonne}, this);
    }

    // for (int ligne = 0; ligne < 8; ligne++){
    //     for (int colonne = 0; colonne < 8; colonne++){
    //         plateau_[ligne][colonne] = new Piece(this);
    //     }
    // }
    // delete plateau_[3][5];
    // plateau_[3][5] = new Pion(Couleur::Noir, {3, 5}, this);

    // delete plateau_[4][4];
    // plateau_[4][4] = new Pion(Couleur::Blanc, {4, 4}, this);

    // delete plateau_[4][6];
    // plateau_[4][6] = new Pion(Couleur::Noir, {4, 6}, this);

    // delete plateau_[1][2];
    // plateau_[1][2] = new Pion(Couleur::Noir, {1, 2}, this);

    // delete plateau_[2][3];
    // plateau_[2][3] = new Pion(Couleur::Blanc, {2, 3}, this);

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

bool ChessBoard::moveTo(std::pair<int, int> coordonneesDepart, std::pair<int, int> coordonneesDestination){
    Piece* pieceDepart = getPieceAt(coordonneesDepart);
    Piece* pieceArrivee= getPieceAt(coordonneesDestination);
    auto mouvementsPossibles = pieceDepart->getMouvementsPossibles();
    auto it = std::find_if(mouvementsPossibles.begin(), mouvementsPossibles.end(), [&](std::pair<int, int> pair){return (pair.first == coordonneesDestination.first) && (pair.second == coordonneesDestination.second);});
    if (it != mouvementsPossibles.end() && isLegalMove(coordonneesDepart, coordonneesDestination)){
        // existe
        if (pieceArrivee->getPieceType() != TypePiece::Vide){
            pieceArrivee->getPieceCouleur() == Couleur::Blanc ? piecesCaptureesBlanc_.push_back(pieceArrivee->getPieceType()) : piecesCaptureesNoir_.push_back(pieceArrivee->getPieceType());
        }
        // equipe diff
        delete plateau_[coordonneesDestination.first][coordonneesDestination.second];
        plateau_[coordonneesDestination.first][coordonneesDestination.second] = pieceDepart;
        plateau_[coordonneesDepart.first][coordonneesDepart.second] = nullptr;
        plateau_[coordonneesDepart.first][coordonneesDepart.second] = new Piece(this);

        pieceDepart->movePiece(coordonneesDestination);
        currentPlayer_ = (currentPlayer_ == Couleur::Blanc) ? Couleur::Noir : Couleur::Blanc;
        return true;
    }
    return false;
}

bool ChessBoard::isLegalMove(std::pair<int, int> coordonneesDepart, std::pair<int, int> coordonneesDestination){
    bool isLegal = false;
    Piece* pieceDepart = getPieceAt(coordonneesDepart);
    Piece* pieceArrivee= getPieceAt(coordonneesDestination);
    std::vector<std::pair<int, int>> mouvementsAdversaire;
    auto mouvementsPossibles = pieceDepart->getMouvementsPossibles();
    auto it = std::find_if(mouvementsPossibles.begin(), mouvementsPossibles.end(), [&](std::pair<int, int> pair){return (pair.first == coordonneesDestination.first) && (pair.second == coordonneesDestination.second);});
    if (it != mouvementsPossibles.end()){
        // existe
        plateau_[coordonneesDestination.first][coordonneesDestination.second] = pieceDepart;
        plateau_[coordonneesDepart.first][coordonneesDepart.second] = nullptr;
        plateau_[coordonneesDepart.first][coordonneesDepart.second] = new Piece(this);

        // pieceDepart->movePiece(coordonneesDestination);

        mouvementsAdversaire = getPossibleMoves(pieceDepart->getPieceCouleur() == Couleur::Blanc ? Couleur::Noir : Couleur::Blanc);
        std::pair<int, int> positionRoi = pieceDepart->getPieceCouleur() == Couleur::Blanc ? positionRoiBlanc : positionRoiNoir;

        if(std::find_if(mouvementsAdversaire.begin(), mouvementsAdversaire.end(), [&](std::pair<int, int> pair){return (pair.first == positionRoi.first) && (pair.second == positionRoi.second);}) == mouvementsAdversaire.end()){
            //roi pas danger
            isLegal = true;
        }

        delete plateau_[coordonneesDepart.first][coordonneesDepart.second];
        plateau_[coordonneesDepart.first][coordonneesDepart.second] = pieceDepart;
        plateau_[coordonneesDestination.first][coordonneesDestination.second] = pieceArrivee;
        // pieceDepart->movePiece(coordonneesDepart);
    }
    return isLegal;
}

std::vector<std::pair<int, int>> ChessBoard::getPossibleMoves(Couleur couleur){
    std::set<std::pair<int, int>> mouvements = {};
    std::vector<std::pair<int, int>> mouvementsTemp = {};
    Piece* pieceTemp = nullptr;
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            pieceTemp = plateau_[ligne][colonne];
            std::vector<std::pair<int, int>> mouvementsPossiblesTemp = pieceTemp->getMouvementsPossibles();
            if (pieceTemp->getPieceType() != TypePiece::Vide && pieceTemp->getPieceCouleur() == couleur){
                for (std::pair<int, int> coordonnee : mouvementsPossiblesTemp){
                    mouvements.insert(coordonnee);
                }
            }
        }
    }
    mouvementsTemp.insert(mouvementsTemp.end(), mouvements.begin(), mouvements.end());
    return mouvementsTemp;
}

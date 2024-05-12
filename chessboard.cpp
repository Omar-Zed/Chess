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
}

ChessBoard::~ChessBoard(){
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            delete plateau_[ligne][colonne];
        }
    }
}

void ChessBoard::resetChessBoard(){
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            delete plateau_[ligne][colonne];
        }
    }

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

    currentPlayer_ = Couleur::Blanc;
    piecesCaptureesBlanc_ = {};
    piecesCaptureesNoir_ = {};
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
    bool roiSafeApresMouvement = isLegalMove(coordonneesDepart, coordonneesDestination);
    if (it != mouvementsPossibles.end() && roiSafeApresMouvement){
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
    // existe
    plateau_[coordonneesDestination.first][coordonneesDestination.second] = pieceDepart;
    plateau_[coordonneesDepart.first][coordonneesDepart.second] = nullptr;
    plateau_[coordonneesDepart.first][coordonneesDepart.second] = new Piece(this);

    mouvementsAdversaire = getPossibleMoves((pieceDepart->getPieceCouleur() == Couleur::Blanc ? Couleur::Noir : Couleur::Blanc));
    std::pair<int, int> positionRoi = getPositionRoi(pieceDepart->getPieceCouleur());

    if(std::find_if(mouvementsAdversaire.begin(), mouvementsAdversaire.end(), [&](std::pair<int, int> pair){return pair == positionRoi;}) == mouvementsAdversaire.end()){
        //roi pas danger
        isLegal = true;
    }

    delete plateau_[coordonneesDepart.first][coordonneesDepart.second];
    plateau_[coordonneesDepart.first][coordonneesDepart.second] = pieceDepart;
    plateau_[coordonneesDestination.first][coordonneesDestination.second] = pieceArrivee;
    return isLegal;
}

std::vector<std::pair<int, int>> ChessBoard::getPossibleMoves(Couleur couleur){
    std::set<std::pair<int, int>> mouvements = {};
    std::vector<std::pair<int, int>> mouvementsTemp = {};
    Piece* pieceTemp = nullptr;
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            pieceTemp = plateau_[ligne][colonne];
            if (pieceTemp->getPieceType() != TypePiece::Vide && pieceTemp->getPieceType() != TypePiece::Roi && pieceTemp->getPieceCouleur() == couleur){
                std::vector<std::pair<int, int>> mouvementsPossiblesTemp = pieceTemp->getMouvementsPossibles();
                for (std::pair<int, int> coordonnee : mouvementsPossiblesTemp){
                    mouvements.insert(coordonnee);
                }
            }
        }
    }
    mouvementsTemp.insert(mouvementsTemp.end(), mouvements.begin(), mouvements.end());
    return mouvementsTemp;
}

std::pair<int, int> ChessBoard::getPositionRoi(Couleur couleur){
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            Piece* piece = getPieceAt({ligne, colonne});
            if (piece->getPieceType() == TypePiece::Roi && piece->getPieceCouleur() == couleur){
                return {ligne, colonne};
            }
        }
    }
    return {0, 0};
}

bool ChessBoard::isCheck(Couleur couleur){
    std::vector<std::pair<int, int>> mouvementsPossibleAdverse = getPossibleMoves(couleur == Couleur::Noir ? Couleur::Blanc : Couleur::Noir);
    auto it = std::find_if(mouvementsPossibleAdverse.begin(), mouvementsPossibleAdverse.end(), [&](std::pair<int, int> mouvement){return mouvement == getPositionRoi(couleur);});
    if(it != mouvementsPossibleAdverse.end()){
        return true;
    }
    return false;
}

bool ChessBoard::isCheckMate(Couleur couleur){
    if (!isCheck(couleur)){
        return false;
    }
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            Piece* piece = getPieceAt({ligne, colonne});
            if (piece->getPieceType() != TypePiece::Vide && piece->getPieceCouleur() == couleur){
                std::vector<std::pair<int, int>> mouvementsPossiblesPiece = piece->getMouvementsPossibles();
                for (std::pair<int, int> mouvement : mouvementsPossiblesPiece){
                    if (isLegalMove({ligne, colonne}, mouvement)){
                        return false; // pas echec et mat
                        std::cout << "{" << ligne << " ; " << colonne << "}" << std::endl;
                    }
                }
            }
        }
    }
    return true; // aucun mouvement possible pour sauver le roi
}

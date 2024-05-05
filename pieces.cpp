#include "pieces.h"
#include "chessboard.h"

const bool isInBoard(std::pair<int, int> coordonnees){return ((coordonnees.first >= 0 && coordonnees.first <= 7) && (coordonnees.second >= 0 && coordonnees.second <= 7));};

Piece::Piece(ChessBoard* plateau) : plateau_(plateau) {

}

Piece::Piece(TypePiece type, Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau) : type_(type), couleur_(couleur), coordonnees_(coordonnees), plateau_(plateau) {

}

const std::vector<std::pair<int, int>>& Piece::getMouvementsPossibles(){
    mouvementsPossibles_ = {};
    if (type_ == TypePiece::Vide){
        return mouvementsPossibles_;
    }
    for (std::pair<int, int> direction : *primitives_){
        for (int multiplicateur = 1; multiplicateur < 8; multiplicateur++){
            std::pair<int, int> nouvellesCoordonnees {coordonnees_.first + direction.first * multiplicateur, coordonnees_.second + direction.second * multiplicateur};
            if (isInBoard(nouvellesCoordonnees)){
                if(plateau_->getPieceAt(nouvellesCoordonnees)->getPieceType() != TypePiece::Vide){
                    //case piece
                    if(plateau_->getPieceAt(nouvellesCoordonnees)->getPieceCouleur() != couleur_){
                        // piece ennemi
                        mouvementsPossibles_.push_back(nouvellesCoordonnees);
                    }
                    break;
                }
                else {
                    //case vide
                    mouvementsPossibles_.push_back(nouvellesCoordonnees);
                }
            }
            else{
                break;
            }
        }
    }
    return mouvementsPossibles_;
}


Roi::Roi(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau)
    : Piece(TypePiece::Roi, couleur, coordonnees, plateau)
{
    primitives_ = &KingMovements;
}

Reine::Reine(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau)
    : Piece(TypePiece::Reine, couleur, coordonnees, plateau)
{
    primitives_ = &QueenMovements;
}

Tour::Tour(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau)
    : Piece(TypePiece::Tour, couleur, coordonnees, plateau)
{
    primitives_ = &RookMovements;
}

Cavalier::Cavalier(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau)
    : Piece(TypePiece::Cavalier, couleur, coordonnees, plateau)
{
    primitives_ = &KnightMovements;
}

Fou::Fou(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau)
    : Piece(TypePiece::Fou, couleur, coordonnees, plateau)
{
    primitives_ = &BishopMovements;
}

Pion::Pion(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau)
    : Piece(TypePiece::Pion, couleur, coordonnees, plateau)
{
    primitives_ = &PawnMovements;
    if ((couleur_ == Couleur::Blanc && coordonnees_.first == 6) || (couleur_ == Couleur::Noir && coordonnees_.first == 1)){
        isFistMove = true;
    }
    else {
        isFistMove = false;
    }
}

const std::vector<std::pair<int, int>>& Pion::getMouvementsPossibles(){
    mouvementsPossibles_ = {};
    int direction = (couleur_ == Couleur::Blanc) ? -1 : 1;
    for (int multiplicateur = 1; multiplicateur <= (isFistMove ? 2 : 1); multiplicateur ++){
        std::pair<int, int> nouvellesCoordonnees {coordonnees_.first + direction * multiplicateur, coordonnees_.second};
        if (isInBoard(nouvellesCoordonnees)){
            if(plateau_->getPieceAt(nouvellesCoordonnees)->getPieceType() != TypePiece::Vide){
                //case piece
                if(plateau_->getPieceAt(nouvellesCoordonnees)->getPieceCouleur() != couleur_){
                    // piece ennemi
                    mouvementsPossibles_.push_back(nouvellesCoordonnees);
                }
                break;
            }
            else {
                //case vide
                mouvementsPossibles_.push_back(nouvellesCoordonnees);
            }
        }
        else{
            break;
        }
    }

    for (int colonne = -1; colonne <= 1; colonne += 2){
        std::pair<int, int> nouvellesCoordonnees {coordonnees_.first + direction, coordonnees_.second + colonne};
        if (isInBoard(nouvellesCoordonnees)){
            if(plateau_->getPieceAt(nouvellesCoordonnees)->getPieceType() != TypePiece::Vide){
                //case piece
                if(plateau_->getPieceAt(nouvellesCoordonnees)->getPieceCouleur() != couleur_){
                    // piece ennemi
                    mouvementsPossibles_.push_back(nouvellesCoordonnees);
                }
            }
        }
    }

    return mouvementsPossibles_;
}


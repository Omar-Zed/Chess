#include "pieces.h"

Piece::Piece(ChessBoard* plateau) : plateau_(plateau) {

}

Piece::Piece(TypePiece type, Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau) : type_(type), couleur_(couleur), coordonnees_(coordonnees), plateau_(plateau) {

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
}

void Pion::getMouvementsPossibles(){

}

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "pieces.h"
#include <memory>

class ChessBoard
{
public:
    ChessBoard();
    void debugChessBoard();

    Piece* const getPieceAt(std::pair<int, int> coordonnees) const {return plateau_[coordonnees.first][coordonnees.second];};
    bool moveTo(std::pair<int, int> coordonneesDepart, std::pair<int, int> coordonneesDestination);
    bool isLegalMove(std::pair<int, int> coordonneesDepart, std::pair<int, int> coordonneesDestination);
    Couleur const getCurrentPlayer() const {return currentPlayer_;};
    std::vector<std::pair<int, int>> getPossibleMoves(Couleur couleur);

    std::pair<int, int> positionRoiBlanc;
    std::pair<int, int> positionRoiNoir;

private:
    Piece* plateau_[8][8] = {};
    bool isWhiteCheck_ = false;
    bool isBlackChecl_ = false;
    std::vector<TypePiece> piecesCaptureesBlanc_ {};
    std::vector<TypePiece> piecesCaptureesNoir_ {};
    Couleur currentPlayer_ = Couleur::Blanc;
};

#endif // CHESSBOARD_H

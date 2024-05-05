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
private:
    Piece* plateau_[8][8] = {};
    bool isWhiteCheck_ = false;
    bool isBlackChecl_ = false;
    std::vector<std::pair<int, int>> mouvementsPossibleBlanc_ {};
    std::vector<std::pair<int, int>> mouvementsPossibleNoir_ {};
    std::vector<TypePiece> piecesCaptureesBlanc_ {};
    std::vector<TypePiece> piecesCaptureesNoir_ {};
};

#endif // CHESSBOARD_H

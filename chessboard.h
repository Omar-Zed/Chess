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
private:
    Piece* plateau_[8][8] = {};
    bool isWhiteCheck = false;
    bool isBlackChecl = false;
    std::vector<std::pair<int, int>> mouvementsPossibleBlanc {};
    std::vector<std::pair<int, int>> mouvementsPossibleNoir {};
    std::vector<TypePiece> piecesCaptureesBlanc {};
    std::vector<TypePiece> piecesCaptureesNoir{};
};

#endif // CHESSBOARD_H

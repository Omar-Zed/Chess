#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "pieces.h"
#include <memory>

class ChessBoard
{
public:
    ChessBoard();
private:
    std::shared_ptr<Piece> plateau_[8][8] = {};
};

#endif // CHESSBOARD_H
